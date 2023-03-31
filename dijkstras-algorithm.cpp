#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#define range 999999


using namespace std;


// Declaring necessary variables 
int adj_matrix[9999][9999]; 
int dist[9999]; 
bool visited[9999]; 


// Initialize distance and visited arrays
void initialize(int start, int num_nodes) 
{
    for(int i = 0; i < num_nodes; i++) 
    {
        dist[i] = range;
        visited[i] = false;
    }
    dist[start] = 0;
}


// Find the node with minimum distance
int findMinNode(int num_nodes) 
{
    int minDist = range;
    int minNode = -1;
    for(int j = 0; j < num_nodes; j++) 
    {
        if(!visited[j] && dist[j] < minDist) 
        {
            minDist = dist[j];
            minNode = j;
        }
    }
    return minNode;
}


// Update the distance
void updateDistances(int minNode, int num_nodes) 
{
    for(int j = 0; j < num_nodes; j++) 
    {
        if(!visited[j] && adj_matrix[minNode][j] != range && dist[minNode] + adj_matrix[minNode][j] < dist[j]) 
        {
            dist[j] = dist[minNode] + adj_matrix[minNode][j];
        }
    }
}


// Print the shortest path
void printShortestPath(int start, int end, int num_nodes) 
{
    // Check if the distance is range, means no path exists
    if(dist[end] == range) 
    {
        cout << "No path exists!" << endl;
        return;
    }
    cout << "Shortest path:";
    int node = end;
    string path = to_string(node);

    // Recursively print the shortest path
    while(node != start) 
    {
        for(int i = 0; i < num_nodes; i++) 
        {
            if(adj_matrix[i][node] != range && dist[i] + adj_matrix[i][node] == dist[node]) 
            {
                node = i;
                path = to_string(node) + " " + path;
                break;
            }
        }
    }
    cout << path << endl;
    cout << "Total distance:" << dist[end] << endl;
}


// Dijkstra's algorithm
void dijkstra(int start, int end, int num_nodes) 
{
    initialize(start, num_nodes);

    // Find nodes and update min distances
    for(int i = 0; i < num_nodes - 1; i++) 
    {
        int minNode = findMinNode(num_nodes);
        visited[minNode] = true;
        updateDistances(minNode, num_nodes);
    }
    printShortestPath(start, end, num_nodes);
}


int main() {
    // Open input files
    string path = "./graph_data_1.txt";
    ifstream inf(path);
    
    if(!inf.is_open()) 
    {
        cout << "Can't open file!" << endl;
        return 1;
    }

    // Activate the exception handling of inf stream  
    // inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // Read number of nodes
    int num_nodes;
    inf >> num_nodes;

    // Initialize graph
    for(int i = 0; i < num_nodes; i++) 
    {
        for(int j = 0; j < num_nodes; j++) 
        {
            adj_matrix[i][j] = range;
        }
    }

    // Connect edges with weights
    int v1, v2, distance;
    while(inf >> v1 >> v2 >> distance) 
    {
        adj_matrix[v1][v2] = distance;
        adj_matrix[v2][v1] = distance; // For undirected graph
    }

    // Read codes from 2nd file
    ifstream inf2("./graph_data_2.txt");
    if(!inf2.is_open()) 
    {
        cout << "Can't open file!" << endl;
        return 1;
    }

    // Read building mapping from 2nd file
    int num_buildings;
    inf2 >> num_buildings;

    // Map_code for buildings
    unordered_map<string, int> map_codes; 

    // Intialize codes
    for(int i = 0; i < num_buildings; i++) 
    {
        int id;
        string code;
        inf2 >> id >> code;
        map_codes[code] = id;
    }

    // Start and end buildings
    string b1, b2;
    cout << "Enter start building:";
    cin >> b1;
    cout << "Enter end building:";
    cin >> b2;

    // Check if building codes are valid
    if(map_codes.find(b1) == map_codes.end() || map_codes.find(b2) == map_codes.end()) 
    {
        // If not valid
        cout << "Please enter correct code!" << endl;
        return 1;
    }

    // If valid
    else
    {
        // Find node number
        int start = map_codes[b1];
        int end = map_codes[b2];

        // Dijkstra's algorithm
        dijkstra(start, end, num_nodes);
    }

    return 0;
}

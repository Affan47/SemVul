dfs(int neighbour, int* colors, Graph graph[],int* control_set){
  int* adjs = graph[neighbour].adjacents;
  int adjs_size = graph[neighbour].adj_size;
  int i = 0;
  int vertex;


  control_set[neighbour]=1;


  while (i<adjs_size){
    vertex=adjs[i];


    if (! control_set[vertex]&&
        (colors[0]==graph[vertex].color||
         colors[1]==graph[vertex].color) ){
      dfs(vertex,colors,graph,control_set);
    }
    ++i;
  }
}

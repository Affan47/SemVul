genFC(int vert,
	   int* FC,
	   int FC_size,
	   Graph* graph,
	   int* satur_degree,
	   int upper_bound){
  int i;
  int* color_around = graph[vert].color_around;

  for(i=0; i <= FC_size; ++i){
    if (color_around[i]>0)
      FC[i]=0;
    else
      FC[i]=1;
  }
}

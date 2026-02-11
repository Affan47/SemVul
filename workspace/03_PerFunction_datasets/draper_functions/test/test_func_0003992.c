coalease_graph(int src, int dest){
	int i,j,k;
	i = dest;
	while(i != src){
		j = check_pred(node1[i].pred);
		k = check_pred(i);


		node[k].pred = j;
		i = node1[i].pred;
	}

}

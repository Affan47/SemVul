insertpt(NODE pt,int id){

	int pt_idx = allocate_node();
	if(pt_idx == -1)
		report_exit("Can not find available position for inserting!");

#ifdef DEBUG
	printf("allocated:%d\n",pt_idx);
#endif
	mapping[pt_idx] = id;
	int i;
	g_node[pt_idx] = pt;
	for(i=0;i<g_size;i++){
		if( i!=pt_idx && g_occupy[i] == TRUE &&
		    use_corner[i] == TRUE ){


			reach(pt,g_node[i],pt_idx,i);

		}
	}
	++g_num;
	dirty=TRUE;
	return pt_idx;
}

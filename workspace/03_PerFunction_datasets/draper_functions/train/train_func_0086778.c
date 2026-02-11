all_flags_set()
{
	int i;
	for(i=0;i<total_nodes;i++)
	{
		if(node[i].flag==0)
			return 0;
	}
	return 1;
}

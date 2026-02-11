find_degree1_edge(graph_t *g, cmph_uint32 v, cmph_uint8 *deleted, cmph_uint32 *e)
{
	cmph_uint32 edge = g->first[v];
	cmph_uint8 found = 0;
	DEBUGP("Checking degree of vertex %u\n", v);
	if (edge == EMPTY) return 0;
	else if (!(GETBIT(deleted, abs_edge(edge, 0))))
	{
		found = 1;
		*e = edge;
	}
	while(1)
	{
		edge = g->next[edge];
		if (edge == EMPTY) break;
		if (GETBIT(deleted, abs_edge(edge, 0))) continue;
		if (found) return 0;
		DEBUGP("Found first edge\n");
		*e = edge;
		found = 1;
	}
	return found;
}

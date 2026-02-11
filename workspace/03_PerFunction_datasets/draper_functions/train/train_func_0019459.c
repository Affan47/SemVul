gar_read_graph(struct gar_subfile *sub, int frclass, u_int32_t from, int dstclass, u_int32_t to)
{
	struct gar_graph *g;
	struct node *pos, *dest;

	g = gar_alloc_graph(sub);
	if (!g)
		return NULL;
	pos = gar_get_node(g, from);
	pos->class = frclass;
	g->pos  = pos;
	if (dstclass != 1000) {
		dest = gar_get_node(g, to);
		dest->class = dstclass;
		g->dest = dest;
	}
	g->valid = gar_load_next_class(g);
	return g;
}

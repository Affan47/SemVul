graph_has_any_edge(struct isl_sched_graph *graph,
	struct isl_sched_node *src, struct isl_sched_node *dst)
{
	enum isl_edge_type i;
	int r;

	for (i = isl_edge_first; i <= isl_edge_last; ++i) {
		r = graph_has_edge(graph, i, src, dst);
		if (r < 0 || r)
			return r;
	}

	return r;
}

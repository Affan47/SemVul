compute_max_row(struct isl_sched_graph *graph,
	__isl_keep isl_union_set *domain)
{
	graph->n = 0;
	graph->maxvar = 0;
	if (isl_union_set_foreach_set(domain, &init_n_maxvar, graph) < 0)
		return -1;
	graph->max_row = graph->n + 2 * graph->maxvar;

	return 0;
}

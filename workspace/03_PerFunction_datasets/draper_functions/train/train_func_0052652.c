compute_sub_schedule(isl_ctx *ctx,
	struct isl_sched_graph *graph, int n, int n_edge,
	int (*node_pred)(struct isl_sched_node *node, int data),
	int (*edge_pred)(struct isl_sched_edge *edge, int data),
	int data, int wcc)
{
	struct isl_sched_graph split = { 0 };
	int t;

	if (graph_alloc(ctx, &split, n, n_edge) < 0)
		goto error;
	if (copy_nodes(&split, graph, node_pred, data) < 0)
		goto error;
	if (graph_init_table(ctx, &split) < 0)
		goto error;
	for (t = 0; t <= isl_edge_last; ++t)
		split.max_edge[t] = graph->max_edge[t];
	if (graph_init_edge_tables(ctx, &split) < 0)
		goto error;
	if (copy_edges(ctx, &split, graph, edge_pred, data) < 0)
		goto error;
	split.n_row = graph->n_row;
	split.max_row = graph->max_row;
	split.n_total_row = graph->n_total_row;
	split.n_band = graph->n_band;
	split.band_start = graph->band_start;

	if (wcc && compute_schedule_wcc(ctx, &split) < 0)
		goto error;
	if (!wcc && compute_schedule(ctx, &split) < 0)
		goto error;

	copy_schedule(graph, &split, node_pred, data);

	graph_free(ctx, &split);
	return 0;
error:
	graph_free(ctx, &split);
	return -1;
}

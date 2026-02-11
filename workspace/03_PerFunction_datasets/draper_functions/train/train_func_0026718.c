compute_next_band(
	__isl_take isl_schedule_node *node,
	struct isl_sched_graph *graph, int permutable)
{
	isl_ctx *ctx;

	if (!node)
		return NULL;

	ctx = isl_schedule_node_get_ctx(node);
	if (update_edges(ctx, graph) < 0)
		return isl_schedule_node_free(node);
	node = insert_current_band(node, graph, permutable);
	next_band(graph);

	node = isl_schedule_node_child(node, 0);
	node = compute_schedule(node, graph);
	node = isl_schedule_node_parent(node);

	return node;
}

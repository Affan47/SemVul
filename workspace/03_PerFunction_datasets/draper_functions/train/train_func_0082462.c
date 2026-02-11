compute_schedule(isl_schedule_node *node,
	struct isl_sched_graph *graph)
{
	isl_ctx *ctx;

	if (!node)
		return NULL;

	ctx = isl_schedule_node_get_ctx(node);
	if (ctx->opt->schedule_fuse == ISL_SCHEDULE_FUSE_MIN) {
		if (detect_sccs(ctx, graph) < 0)
			return isl_schedule_node_free(node);
	} else {
		if (detect_wccs(ctx, graph) < 0)
			return isl_schedule_node_free(node);
	}

	if (graph->scc > 1)
		return compute_component_schedule(node, graph, 1);

	return compute_schedule_wcc(node, graph);
}

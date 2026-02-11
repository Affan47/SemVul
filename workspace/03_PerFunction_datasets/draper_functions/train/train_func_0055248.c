compute_component_schedule(isl_ctx *ctx,
	struct isl_sched_graph *graph)
{
	int wcc, i;
	int n, n_edge;
	int n_total_row, orig_total_row;
	int n_band, orig_band;

	if (ctx->opt->schedule_fuse == ISL_SCHEDULE_FUSE_MIN ||
	    ctx->opt->schedule_separate_components)
		if (split_on_scc(ctx, graph) < 0)
			return -1;

	n_total_row = 0;
	orig_total_row = graph->n_total_row;
	n_band = 0;
	orig_band = graph->n_band;
	for (i = 0; i < graph->n; ++i)
		graph->node[i].band_id[graph->n_band] += graph->node[i].scc;
	for (wcc = 0; wcc < graph->scc; ++wcc) {
		n = 0;
		for (i = 0; i < graph->n; ++i)
			if (graph->node[i].scc == wcc)
				n++;
		n_edge = 0;
		for (i = 0; i < graph->n_edge; ++i)
			if (graph->edge[i].src->scc == wcc &&
			    graph->edge[i].dst->scc == wcc)
				n_edge++;

		if (compute_sub_schedule(ctx, graph, n, n_edge,
				    &node_scc_exactly,
				    &edge_scc_exactly, wcc, 1) < 0)
			return -1;
		if (graph->n_total_row > n_total_row)
			n_total_row = graph->n_total_row;
		graph->n_total_row = orig_total_row;
		if (graph->n_band > n_band)
			n_band = graph->n_band;
		graph->n_band = orig_band;
	}

	graph->n_total_row = n_total_row;
	graph->n_band = n_band;

	return pad_schedule(graph);
}

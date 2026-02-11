graph_free(isl_ctx *ctx, struct isl_sched_graph *graph)
{
	int i;

	isl_map_to_basic_set_free(graph->intra_hmap);
	isl_map_to_basic_set_free(graph->inter_hmap);

	for (i = 0; i < graph->n; ++i) {
		isl_space_free(graph->node[i].dim);
		isl_mat_free(graph->node[i].sched);
		isl_map_free(graph->node[i].sched_map);
		isl_mat_free(graph->node[i].cmap);
		isl_mat_free(graph->node[i].cinv);
		if (graph->root) {
			free(graph->node[i].band);
			free(graph->node[i].band_id);
			free(graph->node[i].coincident);
		}
	}
	free(graph->node);
	free(graph->sorted);
	for (i = 0; i < graph->n_edge; ++i) {
		isl_map_free(graph->edge[i].map);
		isl_union_map_free(graph->edge[i].tagged_condition);
		isl_union_map_free(graph->edge[i].tagged_validity);
	}
	free(graph->edge);
	free(graph->region);
	for (i = 0; i <= isl_edge_last; ++i)
		isl_hash_table_free(ctx, graph->edge_table[i]);
	isl_hash_table_free(ctx, graph->node_table);
	isl_basic_set_free(graph->lp);
}

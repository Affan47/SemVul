add_intra_proximity_constraints(struct isl_sched_graph *graph,
	struct isl_sched_edge *edge, int s, int local)
{
	unsigned total;
	unsigned nparam;
	isl_map *map = isl_map_copy(edge->map);
	isl_ctx *ctx = isl_map_get_ctx(map);
	isl_space *dim;
	isl_dim_map *dim_map;
	isl_basic_set *coef;
	struct isl_sched_node *node = edge->src;

	coef = intra_coefficients(graph, node, map);

	dim = isl_space_domain(isl_space_unwrap(isl_basic_set_get_space(coef)));

	coef = isl_basic_set_transform_dims(coef, isl_dim_set,
		    isl_space_dim(dim, isl_dim_set), isl_mat_copy(node->cmap));
	if (!coef)
		goto error;

	nparam = isl_space_dim(node->space, isl_dim_param);
	total = isl_basic_set_total_dim(graph->lp);
	dim_map = isl_dim_map_alloc(ctx, total);

	if (!local) {
		isl_dim_map_range(dim_map, 1, 0, 0, 0, 1, 1);
		isl_dim_map_range(dim_map, 4, 2, 1, 1, nparam, -1);
		isl_dim_map_range(dim_map, 5, 2, 1, 1, nparam, 1);
	}
	isl_dim_map_range(dim_map, node->start + 2 * node->nparam + 1, 2,
			  isl_space_dim(dim, isl_dim_set), 1,
			  node->nvar, s);
	isl_dim_map_range(dim_map, node->start + 2 * node->nparam + 2, 2,
			  isl_space_dim(dim, isl_dim_set), 1,
			  node->nvar, -s);
	graph->lp = isl_basic_set_extend_constraints(graph->lp,
			coef->n_eq, coef->n_ineq);
	graph->lp = isl_basic_set_add_constraints_dim_map(graph->lp,
							   coef, dim_map);
	isl_space_free(dim);

	return 0;
error:
	isl_space_free(dim);
	return -1;
}

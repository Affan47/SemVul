generate_parallel_domains(
	__isl_keep isl_basic_set_list *domain_list,
	__isl_keep isl_union_map *executed, __isl_keep isl_ast_build *build)
{
	int i, n;
	isl_ctx *ctx;
	isl_ast_graft_list *list;
	struct isl_shared_outer_data data;
	struct isl_tarjan_graph *g;

	if (!domain_list)
		return NULL;

	n = isl_basic_set_list_n_basic_set(domain_list);
	if (n <= 1)
		return generate_sorted_domains(domain_list, executed, build);

	ctx = isl_basic_set_list_get_ctx(domain_list);

	data.depth = isl_ast_build_get_depth(build);
	data.piece = domain_list->p;
	g = isl_tarjan_graph_init(ctx, n, &shared_outer, &data);
	if (!g)
		return NULL;

	i = 0;
	do {
		int first;
		isl_ast_graft_list *list_c;

		if (g->order[i] == -1)
			isl_die(ctx, isl_error_internal, "cannot happen",
				break);
		first = i;
		while (g->order[i] != -1) {
			++i; --n;
		}
		if (first == 0 && n == 0) {
			isl_tarjan_graph_free(g);
			return generate_sorted_domains(domain_list,
							executed, build);
		}
		list_c = generate_sorted_domains_part(domain_list,
				g->order + first, i - first, executed, build);
		list_c = isl_ast_graft_list_fuse(list_c, build);
		if (first == 0)
			list = list_c;
		else
			list = isl_ast_graft_list_concat(list, list_c);
		++i;
	} while (list && n);

	if (n > 0)
		list = isl_ast_graft_list_free(list);

	list = isl_ast_graft_list_sort(list);

	isl_tarjan_graph_free(g);

	return list;
}

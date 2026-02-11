union_components(
	__isl_take isl_union_map *umap, int *exact)
{
	int i;
	int n;
	isl_ctx *ctx;
	isl_basic_map **list = NULL;
	isl_basic_map **next;
	isl_union_map *path = NULL;
	struct isl_tc_follows_data data;
	struct isl_tarjan_graph *g = NULL;
	int c, l;
	int recheck = 0;

	n = 0;
	if (isl_union_map_foreach_map(umap, inc_count, &n) < 0)
		goto error;

	if (n <= 1)
		return union_floyd_warshall(umap, exact);

	ctx = isl_union_map_get_ctx(umap);
	list = isl_calloc_array(ctx, isl_basic_map *, n);
	if (!list)
		goto error;

	next = list;
	if (isl_union_map_foreach_map(umap, collect_basic_map, &next) < 0)
		goto error;

	data.list = list;
	data.check_closed = 0;
	g = isl_tarjan_graph_init(ctx, n, &basic_map_follows, &data);
	if (!g)
		goto error;

	c = 0;
	i = 0;
	l = n;
	path = isl_union_map_empty(isl_union_map_get_space(umap));
	while (l) {
		isl_union_map *comp;
		isl_union_map *path_comp, *path_comb;
		comp = isl_union_map_empty(isl_union_map_get_space(umap));
		while (g->order[i] != -1) {
			comp = isl_union_map_add_map(comp,
				    isl_map_from_basic_map(
					isl_basic_map_copy(list[g->order[i]])));
			--l;
			++i;
		}
		path_comp = union_floyd_warshall(comp, exact);
		path_comb = isl_union_map_apply_range(isl_union_map_copy(path),
						isl_union_map_copy(path_comp));
		path = isl_union_map_union(path, path_comp);
		path = isl_union_map_union(path, path_comb);
		++i;
		++c;
	}

	if (c > 1 && data.check_closed && !*exact) {
		int closed;

		closed = isl_union_map_is_transitively_closed(path);
		if (closed < 0)
			goto error;
		recheck = !closed;
	}

	isl_tarjan_graph_free(g);

	for (i = 0; i < n; ++i)
		isl_basic_map_free(list[i]);
	free(list);

	if (recheck) {
		isl_union_map_free(path);
		return union_floyd_warshall(umap, exact);
	}

	isl_union_map_free(umap);

	return path;
error:
	isl_tarjan_graph_free(g);
	if (list) {
		for (i = 0; i < n; ++i)
			isl_basic_map_free(list[i]);
		free(list);
	}
	isl_union_map_free(umap);
	isl_union_map_free(path);
	return NULL;
}

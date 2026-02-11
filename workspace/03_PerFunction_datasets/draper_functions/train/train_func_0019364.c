collect_sink_source(__isl_keep isl_schedule_node *node, void *user)
{
	struct isl_compute_flow_schedule_data *data = user;
	isl_union_map *prefix;
	isl_union_map *umap;
	int r = 0;

	if (isl_schedule_node_get_type(node) != isl_schedule_node_leaf)
		return 1;

	data->node = node;

	prefix = isl_schedule_node_get_prefix_schedule_union_map(node);
	prefix = isl_union_map_reverse(prefix);
	prefix = isl_union_map_range_map(prefix);

	data->set_sink = 1;
	umap = isl_union_map_copy(data->access->sink);
	umap = isl_union_map_apply_range(isl_union_map_copy(prefix), umap);
	if (isl_union_map_foreach_map(umap, &extract_sink_source, data) < 0)
		r = -1;
	isl_union_map_free(umap);

	data->set_sink = 0;
	data->must = 1;
	umap = isl_union_map_copy(data->access->must_source);
	umap = isl_union_map_apply_range(isl_union_map_copy(prefix), umap);
	if (isl_union_map_foreach_map(umap, &extract_sink_source, data) < 0)
		r = -1;
	isl_union_map_free(umap);

	data->set_sink = 0;
	data->must = 0;
	umap = isl_union_map_copy(data->access->may_source);
	umap = isl_union_map_apply_range(isl_union_map_copy(prefix), umap);
	if (isl_union_map_foreach_map(umap, &extract_sink_source, data) < 0)
		r = -1;
	isl_union_map_free(umap);

	isl_union_map_free(prefix);

	return r;
}

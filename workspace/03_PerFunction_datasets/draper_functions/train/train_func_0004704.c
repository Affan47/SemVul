collect_filter_prefix(__isl_keep isl_schedule_tree_list *list,
	int n, struct isl_schedule_node_get_filter_prefix_data *data)
{
	int i;

	if (!list)
		return -1;

	for (i = n - 1; i >= 0; --i) {
		isl_schedule_tree *tree;
		enum isl_schedule_node_type type;
		int r;

		tree = isl_schedule_tree_list_get_schedule_tree(list, i);
		if (!tree)
			return -1;
		type = isl_schedule_tree_get_type(tree);
		if (type == isl_schedule_node_expansion)
			return collect_filter_prefix_expansion(tree, list, i,
								data);
		if (type == isl_schedule_node_extension &&
		    data->universe_domain && !data->collect_prefix)
			return collect_universe_domain_extension(tree, list, i,
								data);
		if (!data->initialized)
			r = collect_filter_prefix_init(tree, data);
		else
			r = collect_filter_prefix_update(tree, data);
		isl_schedule_tree_free(tree);
		if (r < 0)
			return -1;
	}

	return 0;
}

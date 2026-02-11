isl_schedule_node_band_sink(
	__isl_take isl_schedule_node *node)
{
	enum isl_schedule_node_type type;
	isl_schedule_tree *tree, *child;
	int anchored;

	if (!node)
		return NULL;

	type = isl_schedule_node_get_type(node);
	if (type != isl_schedule_node_band)
		isl_die(isl_schedule_node_get_ctx(node), isl_error_invalid,
			"not a band node", isl_schedule_node_free(node));
	anchored = isl_schedule_node_is_subtree_anchored(node);
	if (anchored < 0)
		return isl_schedule_node_free(node);
	if (anchored)
		isl_die(isl_schedule_node_get_ctx(node), isl_error_invalid,
			"cannot sink band node in anchored subtree",
			isl_schedule_node_free(node));
	if (isl_schedule_tree_n_children(node->tree) == 0)
		return node;

	tree = isl_schedule_node_get_tree(node);
	child = isl_schedule_tree_get_child(tree, 0);
	tree = isl_schedule_tree_reset_children(tree);
	tree = isl_schedule_tree_append_to_leaves(child, tree);

	return isl_schedule_node_graft_tree(node, tree);
}

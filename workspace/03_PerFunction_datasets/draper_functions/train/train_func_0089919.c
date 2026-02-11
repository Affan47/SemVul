fm_tree_model_iter_children (GtkTreeModel *model, GtkTreeIter *iter, GtkTreeIter *parent_iter)
{
	TreeNode *parent;

	g_return_val_if_fail (FM_IS_TREE_MODEL (model), FALSE);
	g_return_val_if_fail (iter_is_valid (FM_TREE_MODEL (model), parent_iter), FALSE);

	parent = parent_iter->user_data;
	if (parent == NULL) {
		return make_iter_invalid (iter);
	}

	if (tree_node_has_dummy_child (parent)) {
		return make_iter_for_dummy_row (parent, iter, parent_iter->stamp);
	}
	return make_iter_for_node (parent->first_child, iter, parent_iter->stamp);
}

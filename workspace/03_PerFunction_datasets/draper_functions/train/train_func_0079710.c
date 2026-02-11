fm_tree_model_ref_node (GtkTreeModel *model, GtkTreeIter *iter)
{
	TreeNode *node, *parent;
#ifdef LOG_REF_COUNTS
	char *uri;
#endif

	g_return_if_fail (FM_IS_TREE_MODEL (model));
	g_return_if_fail (iter_is_valid (FM_TREE_MODEL (model), iter));

	node = iter->user_data;
	if (node == NULL) {
		parent = iter->user_data2;
		g_assert (parent->dummy_child_ref_count >= 0);
		++parent->dummy_child_ref_count;
	} else {
		parent = node->parent;
		g_assert (node->ref_count >= 0);
		++node->ref_count;
	}

	if (parent != NULL) {
		g_assert (parent->all_children_ref_count >= 0);
		if (++parent->all_children_ref_count == 1) {
			if (parent->first_child == NULL) {
				parent->done_loading = FALSE;
			}
			schedule_monitoring_update (FM_TREE_MODEL (model));
		}
#ifdef LOG_REF_COUNTS
		uri = get_node_uri (iter);
		g_message ("ref of %s, count is now %d",
			   uri, parent->all_children_ref_count);
		g_free (uri);
#endif
	}
}

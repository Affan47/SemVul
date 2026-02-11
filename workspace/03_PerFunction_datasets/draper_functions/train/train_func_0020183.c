e_tree_model_generator_get_iter (GtkTreeModel *tree_model,
                                 GtkTreeIter *iter,
                                 GtkTreePath *path)
{
	ETreeModelGenerator *tree_model_generator = E_TREE_MODEL_GENERATOR (tree_model);
	GArray              *group;
	gint                 depth;
	gint                 index = 0;

	g_return_val_if_fail (E_IS_TREE_MODEL_GENERATOR (tree_model), FALSE);
	g_return_val_if_fail (gtk_tree_path_get_depth (path) > 0, FALSE);

	group = tree_model_generator->priv->root_nodes;
	if (!group)
		return FALSE;

	for (depth = 0; depth < gtk_tree_path_get_depth (path); depth++) {
		Node *node;
		gint  child_index;

		index = gtk_tree_path_get_indices (path)[depth];
		child_index = generated_offset_to_child_offset (group, index, NULL);
		if (child_index < 0)
			return FALSE;

		node = &g_array_index (group, Node, child_index);

		if (depth + 1 < gtk_tree_path_get_depth (path)) {
			group = node->child_nodes;
			if (!group)
				return FALSE;
		}
	}

	ITER_SET (tree_model_generator, iter, group, index);
	return TRUE;
}

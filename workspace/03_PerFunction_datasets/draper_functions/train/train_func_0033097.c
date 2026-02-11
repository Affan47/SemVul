collapse_drag (ETree *tree,
               ETreePath drop)
{
	GList *list;


	if (drop) {
		drop = e_tree_model_node_get_parent (tree->priv->model, drop);
	}

	for (list = tree->priv->expanded_list; list; list = list->next) {
		gchar *save_id = list->data;
		ETreePath path;

		path = e_tree_model_get_node_by_id (tree->priv->model, save_id);
		if (path) {
			ETreePath search;
			gboolean found = FALSE;

			for (search = drop; search;
				search = e_tree_model_node_get_parent (
				tree->priv->model, search)) {
				if (path == search) {
					found = TRUE;
					break;
				}
			}

			if (!found)
				e_tree_table_adapter_node_set_expanded (
					tree->priv->etta, path, FALSE);
		}
		g_free (save_id);
	}
	g_list_free (tree->priv->expanded_list);
	tree->priv->expanded_list = NULL;
}

_gtk_tree_model_get_iter_from_attribute_id (GtkTreeModel *tree_model,
					    GtkTreeIter  *root,
					    const char   *attribute_id,
					    GtkTreeIter  *result)
{
	GtkTreeIter  iter;
	char        *iter_id;

	if (root != NULL) {
		gtk_tree_model_get (tree_model,
				    root,
				    ATTRIBUTE_ID_COLUMN, &iter_id,
				    -1);
		if (g_strcmp0 (attribute_id, iter_id) == 0) {
			g_free (iter_id);
			*result = *root;
			return TRUE;
		}

		g_free (iter_id);
	}

	if (! gtk_tree_model_iter_children (tree_model, &iter, root))
		return FALSE;

	do {
		if (_gtk_tree_model_get_iter_from_attribute_id (tree_model, &iter, attribute_id, result))
			return TRUE;
	}
	while (gtk_tree_model_iter_next (tree_model, &iter));

	return FALSE;
}

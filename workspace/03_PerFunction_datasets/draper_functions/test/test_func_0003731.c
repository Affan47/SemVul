keyword_tree_get_iter(GtkTreeModel *keyword_tree, GtkTreeIter *iter_ptr, GList *path)
{
	GtkTreeIter iter;

	if (!gtk_tree_model_get_iter_first(keyword_tree, &iter)) return FALSE;

	while (TRUE)
		{
		GtkTreeIter children;
		while (TRUE)
			{
			gchar *name = keyword_get_name(keyword_tree, &iter);
			if (strcmp(name, path->data) == 0) break;
			g_free(name);
			if (!gtk_tree_model_iter_next(keyword_tree, &iter)) return FALSE;
			}
		path = path->next;
		if (!path)
			{
			*iter_ptr = iter;
			return TRUE;
			}

	    	if (!gtk_tree_model_iter_children(keyword_tree, &children, &iter)) return FALSE;
	    	iter = children;
		}
}

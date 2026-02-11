giggle_tree_view_select_row_by_string (GtkWidget  *treeview,
				       int         column,
				       const char *pattern)
{
	GtkTreeSelection   *selection;
	GtkTreeModel	   *model;
	GtkTreeIter	    iter;
	GtkTreePath        *path;
	char               *text;

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (treeview));

	if (gtk_tree_selection_get_selected (selection, &model, &iter)) {
		gtk_tree_model_get (model, &iter, column, &text, -1);
	} else {
		model = gtk_tree_view_get_model (GTK_TREE_VIEW (treeview));
		text = NULL;
	}

	if (!g_strcmp0 (text, pattern)) {
		g_free (text);
		return TRUE;
	}
	g_free (text);
	text = NULL;

	if (tree_model_find_string (model, &iter, NULL, column, pattern)) {
		path = gtk_tree_model_get_path (model, &iter);
		gtk_tree_view_expand_to_path (GTK_TREE_VIEW (treeview), path);
	 	gtk_tree_path_free (path);

		gtk_tree_selection_select_iter (selection, &iter);

		return TRUE;
	}

	return FALSE;
}

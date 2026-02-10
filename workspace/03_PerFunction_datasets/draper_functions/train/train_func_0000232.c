file_list_status_changed (GiggleFileList *list)
{
	GiggleFileListPriv *priv;
	GtkTreePath        *path;

	if (gtk_tree_view_get_model (GTK_TREE_VIEW (list))) {
		return;
	}

	priv = GET_PRIV (list);
	gtk_tree_view_set_model (GTK_TREE_VIEW (list), priv->filter_model);


	path = gtk_tree_path_new_first ();
	gtk_tree_view_expand_row (GTK_TREE_VIEW (list), path, FALSE);
	gtk_tree_path_free (path);

	if (priv->selected_path)
		giggle_tree_view_select_row_by_string (GTK_WIDGET (list),
						       COL_REL_PATH, priv->selected_path);
}

restore_selection_foreach (GtkTreeModel *model,
			   GtkTreePath *path,
			   GtkTreeIter *iter,
			   gpointer user_data)
{
	RestoreLocationData *data = user_data;
	gchar *uri;

	gtk_tree_model_get (model, iter,
			    PLACES_SIDEBAR_COLUMN_URI, &uri,
			    -1);
	if (g_strcmp0 (uri, data->last_uri) == 0 ||
	    g_strcmp0 (uri, data->location) == 0) {
		data->path = gtk_tree_path_copy (path);
	}

	g_free (uri);

	return (data->path != NULL);
}

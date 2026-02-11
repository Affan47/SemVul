initial_connections_read (NMRemoteSettings *settings, gpointer user_data)
{
	NMConnectionList *list = user_data;
	GtkTreePath *path;
	GtkTreeIter iter;

	g_signal_handlers_disconnect_by_func (settings, G_CALLBACK (initial_connections_read), list);

	if (gtk_tree_model_get_iter_first (GTK_TREE_MODEL (list->sortable), &iter)) {
		path = gtk_tree_model_get_path (GTK_TREE_MODEL (list->sortable), &iter);
		gtk_tree_view_scroll_to_cell (list->connection_list,
		                              path, NULL,
		                              FALSE, 0, 0);
		gtk_tree_path_free (path);
	}
}

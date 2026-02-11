get_selected_connection (CEPageMaster *self)
{
	CEPageMasterPrivate *priv = CE_PAGE_MASTER_GET_PRIVATE (self);
	GtkTreeSelection *selection;
	GList *selected_rows;
	GtkTreeModel *model = NULL;
	GtkTreeIter iter;
	NMRemoteConnection *connection = NULL;

	selection = gtk_tree_view_get_selection (priv->connections);
	selected_rows = gtk_tree_selection_get_selected_rows (selection, &model);
	if (!selected_rows)
		return NULL;

	if (gtk_tree_model_get_iter (model, &iter, (GtkTreePath *) selected_rows->data))
		gtk_tree_model_get (model, &iter, 0, &connection, -1);


	g_list_foreach (selected_rows, (GFunc) gtk_tree_path_free, NULL);
	g_list_free (selected_rows);

	return connection;
}

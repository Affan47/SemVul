on_treeview_changed(GtkWidget *widget, gpointer user_data)
{
	GtkTreeIter 	iter;
	GtkTreeModel 	*model;
	gchar 			*uri;

	if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(widget), &model, &iter))
	{
		gtk_tree_model_get(GTK_TREE_MODEL(treestore), &iter,
							TREEBROWSER_COLUMN_URI, &uri,
							-1);
		if (uri == NULL)
			return;

		if (g_file_test(uri, G_FILE_TEST_EXISTS))
		{
			if (g_file_test(uri, G_FILE_TEST_IS_DIR))
				treebrowser_browse(uri, &iter);
			else
				if (CONFIG_ONE_CLICK_CHDOC)
					document_open_file(uri, FALSE, NULL, NULL);
		}
		else
			gtk_tree_store_iter_clear_nodes(&iter, TRUE);

		g_free(uri);
	}
}

tag2_destroy_browser(tag_browser * browser, gpointer user_data)
{
	GtkTreeIter iter;
	GtkTreeModel *model;
	GtkTreePath *path;
	if (!browser)
	{
		return;
	}


	model = gtk_tree_row_reference_get_model(browser->ref_iter);
	path = gtk_tree_row_reference_get_path(browser->ref_iter);
	if (path)
	{
		if (gtk_tree_model_get_iter(model, &iter, path))
		{
			gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
		}
		gtk_tree_path_free(path);
	}
	gtk_tree_row_reference_free(browser->ref_iter);


	g_free(browser->name);
	g_free(browser->key);

	g_list_foreach(browser->tag_lists, (GFunc) tag2_destroy_tag, NULL);
	g_list_free(browser->tag_lists);

	if (browser->tag2_vbox)
	{
		g_object_unref(browser->tag2_vbox);
	}

	g_free(browser);
}

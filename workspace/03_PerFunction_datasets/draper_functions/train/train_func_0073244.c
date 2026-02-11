fe_url_add (const char *urltext)
{
	GtkListStore *store;
	GtkTreeIter iter;
	gboolean valid;

	if (urlgrabberwindow)
	{
		store = GTK_LIST_STORE (g_object_get_data (G_OBJECT (urlgrabberwindow),
		                                           "model"));
		gtk_list_store_prepend (store, &iter);
		gtk_list_store_set (store, &iter,
		                    URL_COLUMN, urltext,
		                    -1);


		if (prefs.hex_url_grabber_limit > 0)
		{
			valid = gtk_tree_model_iter_nth_child (
				GTK_TREE_MODEL (store), &iter, NULL, prefs.hex_url_grabber_limit);
			while (valid)
				valid = gtk_list_store_remove (store, &iter);
		}
	}
}

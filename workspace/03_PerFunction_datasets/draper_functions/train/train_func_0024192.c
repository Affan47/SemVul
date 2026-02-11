add_bookmark (NemoPlacesSidebar *sidebar)
{
	GtkTreeModel *model;
	GtkTreeIter iter;
	char *uri;
	GFile *location;
	NemoBookmark *bookmark;

	model = gtk_tree_view_get_model (sidebar->tree_view);

	if (get_selected_iter (sidebar, &iter)) {
		gtk_tree_model_get (model, &iter, PLACES_SIDEBAR_COLUMN_URI, &uri, -1);

		if (uri == NULL) {
			return;
		}

		location = g_file_new_for_uri (uri);
		bookmark = nemo_bookmark_new (location, NULL, NULL);

		if (!nemo_bookmark_list_contains (sidebar->bookmarks, bookmark)) {
			nemo_bookmark_list_append (sidebar->bookmarks, bookmark);
		}

		g_object_unref (location);
		g_object_unref (bookmark);
		g_free (uri);
	}
}

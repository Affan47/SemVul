bookmarks_changed_cb (GthMonitor *monitor,
		      DialogData *data)
{
	GBookmarkFile    *bookmarks;
	char             *uri;
	GtkTreeSelection *selection;
	gboolean          selected;

	if (data->entry_changed)
		return;

	uri = gth_uri_list_get_selected (GTH_URI_LIST (data->uri_list));

	g_free (data->last_selected_uri);
	data->last_selected_uri = NULL;

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (data->uri_list));
	g_signal_handlers_block_by_func (selection, uri_list_selection_changed_cb, data);
	bookmarks = gth_main_get_default_bookmarks ();
	gth_uri_list_set_bookmarks (GTH_URI_LIST (data->uri_list), bookmarks);
	g_signal_handlers_unblock_by_func (selection, uri_list_selection_changed_cb, data);

	selected = FALSE;
	if (uri != NULL)
		selected = gth_uri_list_select_uri (GTH_URI_LIST (data->uri_list), uri);

	if (! selected) {


		char **uris;
		char  *last_uri;
		int    i;

		uris = g_bookmark_file_get_uris (bookmarks, NULL);
		last_uri = NULL;
		for (i = 0; uris[i] != NULL; i++)
			last_uri = uris[i];
		if (last_uri != NULL)
			gth_uri_list_select_uri (GTH_URI_LIST (data->uri_list), last_uri);
		else
			set_bookmark_data (data, "", "");

		g_strfreev (uris);
	}

	g_free (uri);
}

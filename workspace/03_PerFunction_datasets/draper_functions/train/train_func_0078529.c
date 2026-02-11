remove_cb (GtkWidget  *widget,
	   DialogData *data)
{
	char          *uri;
	GBookmarkFile *bookmarks;
	GError        *error = NULL;

	uri = gth_uri_list_get_selected (GTH_URI_LIST (data->uri_list));
	if (uri == NULL)
		return;

	bookmarks = gth_main_get_default_bookmarks ();
	if (g_bookmark_file_remove_item (bookmarks, uri, &error)) {
		gth_uri_list_remove_uri (GTH_URI_LIST (data->uri_list), uri);
		gth_main_bookmarks_changed ();
	}
	else {
		_gtk_error_dialog_from_gerror_show (GTK_WINDOW (data->dialog), _("Could not remove the bookmark"), error);
		g_clear_error (&error);
	}

	g_free (uri);
}

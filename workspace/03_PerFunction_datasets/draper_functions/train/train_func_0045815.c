recent_chooser_item_activated_cb (GtkRecentChooser *chooser, GladeWindow *window)
{
	gchar *uri, *path;
	GError *error = NULL;

	uri = gtk_recent_chooser_get_current_uri (chooser);

	path = g_filename_from_uri (uri, NULL, NULL);
	if (error)
	{
		g_warning ("Could not convert uri \"%s\" to a local path: %s", uri, error->message);
		g_error_free (error);
		return;
	}

	glade_window_open_project (window, path);

	g_free (uri);
	g_free (path);
}

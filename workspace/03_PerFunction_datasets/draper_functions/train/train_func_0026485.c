recent_remove (GladeWindow *window, const gchar *path)
{
	gchar *uri;
	GError *error = NULL;

	uri = g_filename_to_uri (path, NULL, &error);
	if (error)
	{
		g_warning ("Could not convert uri \"%s\" to a local path: %s", uri, error->message);
		g_error_free (error);
		return;
	}

	gtk_recent_manager_remove_item (window->priv->recent_manager,
					uri,
					NULL);

	g_free (uri);
}

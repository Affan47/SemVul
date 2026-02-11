xmms_build_playlist_url (const gchar *plspath, const gchar *file)
{
	gchar *url;
	gchar *path;

	g_return_val_if_fail (plspath, NULL);
	g_return_val_if_fail (file, NULL);

	if (strstr (file, "://") != NULL) {
		return g_strdup (file);
	}

	if (file[0] == '/') {
		path = path_get_body (plspath);
		url = g_strconcat (path, file, NULL);
	} else {
		path = path_get_dirname (plspath);
		url = g_strconcat (path, "/", file, NULL);
	}

	g_free (path);
	return url;
}

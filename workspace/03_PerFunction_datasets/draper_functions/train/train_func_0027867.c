gth_thumb_loader_has_valid_thumbnail (GthThumbLoader *self,
				      GthFileData    *file_data)
{
	gboolean  valid_thumbnail = FALSE;
	char     *uri;
	time_t    mtime;
	char     *thumbnail_path;

	uri = g_file_get_uri (file_data->file);
	mtime = gth_file_data_get_mtime (file_data);
	thumbnail_path = gnome_desktop_thumbnail_factory_lookup (self->priv->thumb_factory, uri, mtime);
	if (thumbnail_path != NULL) {
		valid_thumbnail = TRUE;
		g_free (thumbnail_path);
	}

	g_free (uri);

	return valid_thumbnail;
}

brasero_volume_source_open_file (const gchar *path,
				 GError **error)
{
	BraseroVolSrc *src;
	FILE *file;

	file = fopen (path, "r");
	if (!file) {
		int errsv = errno;

		BRASERO_MEDIA_LOG ("open () failed (%s)", g_strerror (errsv));
		g_set_error (error,
			     BRASERO_MEDIA_ERROR,
			     BRASERO_MEDIA_ERROR_GENERAL,
			     "%s",
			     g_strerror (errsv));
		return FALSE;
	}

	src = g_new0 (BraseroVolSrc, 1);
	src->ref = 1;
	src->data = file;
	src->seek = brasero_volume_source_seek_fd;
	src->read = brasero_volume_source_read_fd;
	return src;
}

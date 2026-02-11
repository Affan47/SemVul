brasero_volume_source_read_fd (BraseroVolSrc *src,
			       gchar *buffer,
			       guint blocks,
			       GError **error)
{
	guint64 bytes_read;

	BRASERO_MEDIA_LOG ("Using fread()");

	bytes_read = fread (buffer, 1, ISO9660_BLOCK_SIZE * blocks, src->data);
	if (bytes_read != ISO9660_BLOCK_SIZE * blocks) {
		int errsv = errno;

		BRASERO_MEDIA_LOG ("fread () failed (%s)", g_strerror (errsv));
		g_set_error (error,
			     BRASERO_MEDIA_ERROR,
			     BRASERO_MEDIA_ERROR_GENERAL,
			     "%s",
			     g_strerror (errsv));
		return FALSE;
	}

	return TRUE;
}

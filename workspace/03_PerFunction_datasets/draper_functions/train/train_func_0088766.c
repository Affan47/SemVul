stream_fs_close (CamelStream *stream,
                 GCancellable *cancellable,
                 GError **error)
{
	CamelStreamFsPrivate *priv;

	priv = CAMEL_STREAM_FS_GET_PRIVATE (stream);

	if (g_cancellable_set_error_if_cancelled (cancellable, error))
		return -1;

	if (close (priv->fd) == -1) {
		g_set_error (
			error, G_IO_ERROR,
			g_io_error_from_errno (errno),
			"%s", g_strerror (errno));
		return -1;
	}

	priv->fd = -1;

	return 0;
}

soup_io_stream_close (GIOStream     *stream,
		      GCancellable  *cancellable,
		      GError       **error)
{
	SoupIOStream *siostream = SOUP_IO_STREAM (stream);

	if (siostream->priv->disposing &&
	    !siostream->priv->close_on_dispose)
		return TRUE;

	return g_io_stream_close (siostream->priv->base_iostream,
				  cancellable, error);
}

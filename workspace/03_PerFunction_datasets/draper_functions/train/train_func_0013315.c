read_internal (GInputStream  *stream,
	       void          *buffer,
	       gsize          count,
	       gboolean       blocking,
	       GCancellable  *cancellable,
	       GError       **error)
{
	SoupContentSnifferStream *sniffer = SOUP_CONTENT_SNIFFER_STREAM (stream);
	gssize nread;

	if (sniffer->priv->error) {
		g_propagate_error (error, sniffer->priv->error);
		sniffer->priv->error = NULL;
		return -1;
	}

	if (sniffer->priv->sniffing) {
		nread = read_and_sniff (stream, blocking, cancellable, error);
		if (nread <= 0)
			return nread;
	}

	if (sniffer->priv->buffer) {
		nread = MIN (count, sniffer->priv->buffer_nread);
		memcpy (buffer, sniffer->priv->buffer, nread);
		if (nread == sniffer->priv->buffer_nread) {
			g_free (sniffer->priv->buffer);
			sniffer->priv->buffer = NULL;
		} else {

			memmove (sniffer->priv->buffer,
				 sniffer->priv->buffer + nread,
				 sniffer->priv->buffer_nread - nread);
			sniffer->priv->buffer_nread -= nread;
		}
	} else {
		nread = g_pollable_stream_read (G_FILTER_INPUT_STREAM (stream)->base_stream,
						buffer, count, blocking,
						cancellable, error);
	}
	return nread;
}

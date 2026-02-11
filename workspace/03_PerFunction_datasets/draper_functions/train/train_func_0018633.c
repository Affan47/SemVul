stream_buffer_read (CamelStream *stream,
                    gchar *buffer,
                    gsize n,
                    GCancellable *cancellable,
                    GError **error)
{
	CamelStreamBufferPrivate *priv;
	gssize bytes_read = 1;
	gssize bytes_left;
	gchar *bptr = buffer;
	GError *local_error = NULL;

	priv = CAMEL_STREAM_BUFFER_GET_PRIVATE (stream);

	g_return_val_if_fail (
		(priv->mode & CAMEL_STREAM_BUFFER_MODE) ==
		CAMEL_STREAM_BUFFER_READ, 0);

	while (n && bytes_read > 0) {
		bytes_left = priv->end - priv->ptr;
		if (bytes_left < n) {
			if (bytes_left > 0) {
				memcpy (bptr, priv->ptr, bytes_left);
				n -= bytes_left;
				bptr += bytes_left;
				priv->ptr += bytes_left;
			}

			if (n >= priv->size / 3) {
				bytes_read = camel_stream_read (
					priv->stream, bptr, n,
					cancellable, &local_error);
				if (bytes_read > 0) {
					n -= bytes_read;
					bptr += bytes_read;
				}
			} else {
				bytes_read = camel_stream_read (
					priv->stream, (gchar *) priv->buf,
					priv->size, cancellable, &local_error);
				if (bytes_read > 0) {
					gsize bytes_used = bytes_read > n ? n : bytes_read;
					priv->ptr = priv->buf;
					priv->end = priv->buf + bytes_read;
					memcpy (bptr, priv->ptr, bytes_used);
					priv->ptr += bytes_used;
					bptr += bytes_used;
					n -= bytes_used;
				}
			}
		} else {
			memcpy (bptr, priv->ptr, n);
			priv->ptr += n;
			bptr += n;
			n = 0;
		}
	}


	if (local_error != NULL) {
		if (bptr > buffer)
			g_clear_error (&local_error);
		else {
			g_propagate_error (error, local_error);
			return -1;
		}
	}

	return (gssize)(bptr - buffer);
}

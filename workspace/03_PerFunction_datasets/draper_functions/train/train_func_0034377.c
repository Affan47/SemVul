camel_stream_buffer_gets (CamelStreamBuffer *sbf,
                          gchar *buf,
                          guint max,
                          GCancellable *cancellable,
                          GError **error)
{
	register gchar *outptr, *inptr, *inend, c, *outend;
	gint bytes_read;
	GError *local_error = NULL;

	outptr = buf;
	inptr = (gchar *) sbf->priv->ptr;
	inend = (gchar *) sbf->priv->end;
	outend = buf + max-1;

	do {
		while (inptr < inend && outptr < outend) {
			c = *inptr++;
			*outptr++ = c;
			if (c == '\n') {
				*outptr = 0;
				sbf->priv->ptr = (guchar *) inptr;
				return outptr - buf;
			}
		}
		if (outptr == outend)
			break;

		bytes_read = camel_stream_read (
			sbf->priv->stream, (gchar *) sbf->priv->buf,
			sbf->priv->size, cancellable, &local_error);
		if (bytes_read == -1) {
			if (buf == outptr) {
				if (local_error)
					g_propagate_error (error, local_error);
				return -1;
			} else
				bytes_read = 0;
		}
		sbf->priv->ptr = sbf->priv->buf;
		sbf->priv->end = sbf->priv->buf + bytes_read;
		inptr = (gchar *) sbf->priv->ptr;
		inend = (gchar *) sbf->priv->end;
	} while (bytes_read > 0);

	sbf->priv->ptr = (guchar *) inptr;
	*outptr = 0;

	g_clear_error (&local_error);

	return (gint)(outptr - buf);
}

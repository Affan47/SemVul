stream_read (GMimeStream *stream, char *buf, size_t n)
{
	GMimeStreamFilter *filter = (GMimeStreamFilter *) stream;
	struct _GMimeStreamFilterPrivate *priv = filter->priv;
	struct _filter *f;
	ssize_t nread;

	priv->last_was_read = TRUE;

	if (priv->filteredlen <= 0) {
		size_t presize = READ_PAD;

		nread = g_mime_stream_read (filter->source, priv->buffer, READ_SIZE);
		if (nread <= 0) {

			if (g_mime_stream_eos (filter->source) && !priv->flushed) {
				priv->filtered = priv->buffer;
				priv->filteredlen = 0;
				f = priv->filters;

				while (f != NULL) {
					g_mime_filter_complete (f->filter, priv->filtered, priv->filteredlen,
								presize, &priv->filtered, &priv->filteredlen,
								&presize);
					f = f->next;
				}

				nread = priv->filteredlen;
				priv->flushed = TRUE;
			}

			if (nread <= 0)
				return nread;
		} else {
			priv->filtered = priv->buffer;
			priv->filteredlen = nread;
			priv->flushed = FALSE;
			f = priv->filters;

			while (f != NULL) {
				g_mime_filter_filter (f->filter, priv->filtered, priv->filteredlen, presize,
						      &priv->filtered, &priv->filteredlen, &presize);

				f = f->next;
			}
		}
	}

	nread = MIN (n, priv->filteredlen);
	memcpy (buf, priv->filtered, nread);
	priv->filteredlen -= nread;
	priv->filtered += nread;

	return nread;
}

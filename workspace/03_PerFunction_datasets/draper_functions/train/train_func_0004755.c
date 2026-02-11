stream_write (GMimeStream *stream, const char *buf, size_t n)
{
	GMimeStreamFilter *filter = (GMimeStreamFilter *) stream;
	struct _GMimeStreamFilterPrivate *priv = filter->priv;
	char *buffer = (char *) buf;
	ssize_t nwritten = n;
	struct _filter *f;
	size_t presize;

	priv->last_was_read = FALSE;
	priv->flushed = FALSE;

	f = priv->filters;
	presize = 0;
	while (f != NULL) {
		g_mime_filter_filter (f->filter, buffer, n, presize, &buffer, &n, &presize);

		f = f->next;
	}

	if (g_mime_stream_write (filter->source, buffer, n) == -1)
		return -1;


	return nwritten;
}

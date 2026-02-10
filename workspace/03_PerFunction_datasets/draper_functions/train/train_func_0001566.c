camel_nntp_stream_gets (CamelNNTPStream *is,
                        guchar **start,
                        guint *len,
                        GCancellable *cancellable,
                        GError **error)
{
	gint max;
	guchar *end;

	g_return_val_if_fail (is != NULL, -1);
	g_return_val_if_fail (start != NULL, -1);
	g_return_val_if_fail (len != NULL, -1);

	*len = 0;

	max = is->end - is->ptr;
	if (max == 0) {
		max = nntp_stream_fill (is, cancellable, error);
		if (max <= 0)
			return max;
	}

	*start = is->ptr;
	end = memchr (is->ptr, '\n', max);
	if (end)
		max = (end - is->ptr) + 1;
	*start = is->ptr;
	*len = max;
	is->ptr += max;

	return end == NULL ? 1 : 0;
}

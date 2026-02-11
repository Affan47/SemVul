_g_input_stream_read_all (GInputStream  *istream,
			  void         **buffer,
			  gsize         *size,
			  GCancellable  *cancellable,
			  GError       **error)
{
	gboolean  retval = FALSE;
	void     *local_buffer = NULL;
	char     *tmp_buffer;
	gsize     count;
	gssize    n;

	tmp_buffer = g_new (char, BUFFER_SIZE);
	count = 0;
	for (;;) {
		n = g_input_stream_read (istream, tmp_buffer, BUFFER_SIZE, cancellable, error);
		if (n < 0) {
			g_free (local_buffer);
			retval = FALSE;
			break;
		}
		else if (n == 0) {
			*buffer = local_buffer;
			*size = count;
			retval = TRUE;
			break;
		}


		local_buffer = g_realloc (local_buffer, count + n + 1);
		memcpy (local_buffer + count, tmp_buffer, n);
		count += n;
	}

	g_free (tmp_buffer);

	return retval;
}

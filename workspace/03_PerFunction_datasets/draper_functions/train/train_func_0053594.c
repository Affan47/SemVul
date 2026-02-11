write_references (CamelStream *stream,
                  const gchar *name,
                  const gchar *value,
                  GCancellable *cancellable,
                  GError **error)
{
	GString *buffer;
	const gchar *ids, *ide;
	gssize n_written;
	gsize len;


	buffer = g_string_new (name);
	g_string_append_c (buffer, ':');
	if (!isspace (value[0]))
		g_string_append_c (buffer, ' ');

	len = buffer->len;

	while (*value) {
		ids = value;
		ide = strchr (ids + 1, '>');
		if (ide)
			value = ++ide;
		else
			ide = value = strlen (ids) + ids;

		if (len > 0 && len + (ide - ids) >= CAMEL_FOLD_SIZE) {
			g_string_append_len (buffer, "\n\t", 2);
			len = 0;
		}

		g_string_append_len (buffer, ids, ide - ids);
		len += (ide - ids);
	}

	g_string_append_c (buffer, '\n');

	n_written = camel_stream_write (
		stream, buffer->str, buffer->len, cancellable, error);

	g_string_free (buffer, TRUE);

	return n_written;
}

write_references (GMimeStream *stream, const char *name, const char *value)
{
	GMimeReferences *references, *reference;
	ssize_t nwritten;
	GString *folded;
	size_t len, n;


	references = g_mime_references_decode (value);
	folded = g_string_new (name);
	g_string_append_c (folded, ':');
	len = folded->len;

	reference = references;
	while (reference != NULL) {
		n = strlen (reference->msgid);
		if (len > 1 && len + n + 3 >= GMIME_FOLD_LEN) {
			g_string_append_len (folded, "\n\t", 2);
			len = 1;
		} else {
			g_string_append_c (folded, ' ');
			len++;
		}

		g_string_append_c (folded, '<');
		g_string_append_len (folded, reference->msgid, n);
		g_string_append_c (folded, '>');
		len += n + 2;

		reference = reference->next;
	}

	g_mime_references_clear (&references);

	g_string_append_len (folded, "\n", 1);
	nwritten = g_mime_stream_write (stream, folded->str, folded->len);
	g_string_free (folded, TRUE);

	return nwritten;
}

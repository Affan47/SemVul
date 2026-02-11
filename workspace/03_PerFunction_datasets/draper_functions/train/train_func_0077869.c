_gck_format_some_bytes (GString *output,
                        gconstpointer bytes,
                        gulong length)
{
	guchar ch;
	const guchar *data = bytes;
	gulong i;

	if (bytes == NULL) {
		g_string_append (output, "NULL");
		return;
	}

	g_string_append_c (output, '\"');
	for (i = 0; i < length && i < 128; i++) {
		ch = data[i];
		if (ch == '\t')
			g_string_append (output, "\\t");
		else if (ch == '\n')
			g_string_append (output, "\\n");
		else if (ch == '\r')
			g_string_append (output, "\\r");
		else if (ch >= 32 && ch < 127)
			g_string_append_c (output, ch);
		else
			g_string_append_printf (output, "\\x%02x", ch);
	}

	if (i < length)
		g_string_append_printf (output, "...");
	g_string_append_c (output, '\"');
}

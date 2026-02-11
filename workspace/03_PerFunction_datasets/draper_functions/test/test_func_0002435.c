camel_header_location_decode (const gchar *in)
{
	gint quote = 0;
	GString *out = g_string_new ("");
	gchar c, *res;


	header_decode_lwsp (&in);
	if (*in == '"') {
		in++;
		quote = 1;
	}

	while ((c = *in++)) {
		if (quote && c == '"')
			break;
		if (!camel_mime_is_lwsp (c))
			g_string_append_c (out, c);
	}

	res = g_strdup (out->str);
	g_string_free (out, TRUE);

	return res;
}

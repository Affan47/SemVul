camel_sexp_encode_string (GString *string,
                          const gchar *v_string)
{
	gchar c;
	const gchar *p;

	if (v_string == NULL)
		p = "";
	else
		p = v_string;
	g_string_append (string, " \"");
	while ((c = *p++)) {
		if (c == '\\' || c == '\"' || c == '\'')
			g_string_append_c (string, '\\');
		g_string_append_c (string, c);
	}
	g_string_append (string, "\"");
}

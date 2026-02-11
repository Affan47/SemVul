gbemol_net_escape (const gchar * string)
{
	const gchar *p;
	GString *escaped;

	escaped = g_string_new (NULL);
	p = string;


	while (*p != '\0') {
		if (*p < 0x30 || (*p > 0x39 && *p < 0x41) || (*p > 0x5a && *p < 0x61) || *p > 0x7a) {
			g_string_append_printf (escaped, "%%%02X", (guchar) *p);
		} else {
			g_string_append_c (escaped, *p);
		}
		p++;
	}
	return g_string_free (escaped, FALSE);
}

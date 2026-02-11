escape_string (const gchar *str)
{
	GString *gstr;
	const gchar *iter;

	gstr = g_string_new ("");
	iter = str;
	while (*iter != '\0')
	{
		if (*iter == '>')
			gstr = g_string_append (gstr, "&gt;");
		else if (*iter == '<')
			gstr = g_string_append (gstr, "&lt;");
		else if (*iter == '&')
			gstr = g_string_append (gstr, "&amp;");
		else
			gstr = g_string_append_c (gstr, *iter);
		iter++;
	}
	return g_string_free (gstr, FALSE);
}

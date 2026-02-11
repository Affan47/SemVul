odf_parse_external (char const *start, gchar **external,
		    GnmConventions const *convs)
{
	char const *ptr;
	GString *str;


	if (*start != '\'')
		return start;
	str = g_string_new (NULL);
	ptr = odf_strunescape (start, str, convs);

	if (ptr == NULL || *ptr != '#') {
		g_string_free (str, TRUE);
		return start;
	}

	*external = g_string_free (str, FALSE);
	return (ptr + 1);
}

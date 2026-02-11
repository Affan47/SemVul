str_escape (const char *str, const char *list)
{
	const char *p = str;
	GString *res;

	res = g_string_sized_new (strlen (str));

	for (;;) {
		while (*p && !strchr (list, *p))
			++p;
		g_string_append_len (res, str, p - str);
		if (!*p)
			break;
		g_string_append_c (res, '\\');
		str = p;
		++p;
	}

	return g_string_free (res, FALSE);
}

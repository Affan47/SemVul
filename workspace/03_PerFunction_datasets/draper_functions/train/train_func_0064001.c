expr_name_validate_a1 (const char *name)
{
	const char *p = name;
	gint i;

	for (i = 0; *p && g_ascii_isalpha(p[0]);
	     p = g_utf8_next_char (p))
		i++;
	if (i==0 || i>4)


		return TRUE;
	for (i = 0; *p && g_ascii_isdigit (p[0]);
	     p = g_utf8_next_char (p))
		i++;
	if (i==0)
		return TRUE;
	return (*p != '\0');
}

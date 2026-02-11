to_lower (gchar *str)
{
	gchar *ptr;
	for (ptr = str; *ptr; ptr++)
		*ptr = g_ascii_tolower (*ptr);
	return str;
}

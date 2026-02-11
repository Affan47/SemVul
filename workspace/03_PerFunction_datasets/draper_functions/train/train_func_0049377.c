skip_to_char (gchar *p, gchar c)
{
	while (*p && *p != c) p ++;
	return p;
}

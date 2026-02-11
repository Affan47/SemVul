e2_utf8_escape (const gchar *str, gunichar c)
{
	glong clen = g_utf8_strlen (str, -1);
	glong i;
	gint count = 0;
	const gchar *tmp = str;
	for (i = 0; i < clen; i++)
	{
		if (g_utf8_get_char (tmp) == c)
			count++;
		tmp = g_utf8_next_char (tmp);
	}
	if (count > 0)
	{
		gint len = strlen (str);
		gint size = (len + count + 1) * sizeof (gchar);
		gchar *ret = g_malloc (size);
		count = 0;
		for (i = 0; i < clen; i++)
		{
			gchar *cur = g_utf8_offset_to_pointer (str, i);
			if (g_utf8_get_char (cur) == c)
				g_utf8_strncpy (g_utf8_offset_to_pointer (ret, count++), "\\", 1);
			g_utf8_strncpy (g_utf8_offset_to_pointer (ret, count++), cur, 1);
		}
		ret[size - 1] = '\0';
		return ret;
	} else
		return g_strdup (str);
}

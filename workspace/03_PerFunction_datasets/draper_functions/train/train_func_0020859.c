strstr_nocase (const gchar *haystack,
               const gchar *needle)
{

#ifdef _GNU_SOURCE
	g_return_val_if_fail (haystack, NULL);
	g_return_Val_if_fail (needle, NULL);

	return strcasestr (haystack, needle)
#else

	gchar *l_haystack;
	gchar *l_needle;
	gchar *pos;

	g_return_val_if_fail (haystack, NULL);
	g_return_val_if_fail (needle, NULL);

	l_haystack = g_ascii_strdown (haystack, -1);
	l_needle = g_ascii_strdown (needle, -1);
	pos = strstr (l_haystack, l_needle);


	if (pos)
		pos = (gchar *)(haystack + (pos - l_haystack));

	g_free (l_haystack);
	g_free (l_needle);

	return pos;
#endif
}

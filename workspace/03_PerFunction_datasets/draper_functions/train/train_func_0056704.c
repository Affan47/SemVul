search_all(const gchar * haystack, gchar ** needles)
{

	if (!needles || !*needles)
		return TRUE;

	gchar *uchs = g_utf8_strup(haystack, -1);
	do {
		if (g_strstr_len(uchs, -1, *needles) == NULL) {
			g_free(uchs);
			return FALSE;
		}
		needles++;
	} while (*needles);

	g_free(uchs);
	return TRUE;
}

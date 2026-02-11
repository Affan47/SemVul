eog_pixbuf_get_common_suffix (GdkPixbufFormat *format)
{
	char **extensions;
	int i;
	char *result = NULL;

	if (format == NULL) return NULL;

	extensions = gdk_pixbuf_format_get_extensions (format);
	if (extensions[0] == NULL) return NULL;


	for (i = 0; extensions [i] != NULL; i++) {
		if (strlen (extensions[i]) <= 3) {
			g_free (result);
			result = g_ascii_strdown (extensions[i], -1);
		}
	}


	if (result == NULL) {
		result = g_ascii_strdown (extensions[0], -1);
	}

	g_strfreev (extensions);

	return result;
}

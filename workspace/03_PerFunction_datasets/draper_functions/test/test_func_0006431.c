go_dirname_from_uri (char const *uri, gboolean brief)
{
	char *dirname_utf8, *dirname;
	char *uri_dirname = g_path_get_dirname (uri);
	dirname = uri_dirname ? go_filename_from_uri (uri_dirname) : NULL;
	g_free (uri_dirname);

	if (dirname) {
		char *temp = g_strconcat ("file://", dirname, NULL);
		g_free (dirname);
		dirname = temp;
	}

	if (brief && dirname &&
	    g_ascii_strncasecmp (dirname, "file:///", 8) == 0) {
		char *temp = g_strdup (dirname + 7);
		g_free (dirname);
		dirname = temp;
	}

	dirname_utf8 = dirname ? g_filename_display_name (dirname) : NULL;
	g_free (dirname);
	return dirname_utf8;
}

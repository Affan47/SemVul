_g_file_append_path (GFile      *file,
		     const char *path)
{
	char  *uri;
	char  *escaped;
	char  *new_uri;
	GFile *new_file;

	if (path == NULL)
		return g_file_dup (file);

	uri = g_file_get_uri (file);
	escaped = g_uri_escape_string (path, G_URI_RESERVED_CHARS_ALLOWED_IN_PATH, FALSE);
	new_uri = _g_build_uri (uri, escaped, NULL);
	new_file = g_file_new_for_uri (new_uri);

	g_free (new_uri);
	g_free (escaped);
	g_free (uri);

	return new_file;
}

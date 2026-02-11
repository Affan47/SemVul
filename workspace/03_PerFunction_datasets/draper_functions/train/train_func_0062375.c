prepend_current_dir_if_relative(gchar const *uri)
{
	if (!uri) {
		return NULL;
	}

	gchar *full_path = (gchar *) g_malloc (1001);
	gchar *cwd = g_get_current_dir();

	gsize bytesRead = 0;
	gsize bytesWritten = 0;
	GError* error = NULL;
	gchar* cwd_utf8 = g_filename_to_utf8 ( cwd,
                                                  -1,
                                                  &bytesRead,
                                                  &bytesWritten,
                                                  &error);

	inkscape_rel2abs (uri, cwd_utf8, full_path, 1000);
	gchar *ret = g_strdup (full_path);
	g_free (full_path);
	g_free (cwd);
	return ret;
}

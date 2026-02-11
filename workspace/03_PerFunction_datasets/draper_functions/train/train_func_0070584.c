path_to_utf8(const gchar *path)
#endif
{
	gchar *utf8;
	GError *error = NULL;

	if (!path) return NULL;

	utf8 = g_filename_to_utf8(path, -1, NULL, NULL, &error);
	if (error)
		{
#if GQ_DEBUG_PATH_UTF8
		log_printf("%s:%d: Unable to convert filename to UTF-8:\n%s\n%s\n", file, line, path, error->message);
#else
		log_printf("Unable to convert filename to UTF-8:\n%s\n%s\n", path, error->message);
#endif
		g_error_free(error);
		encoding_dialog(path);
		}
	if (!utf8)
		{

		utf8 = g_strdup(path);
		}

	return utf8;
}

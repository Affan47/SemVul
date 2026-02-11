panel_launcher_get_gfile (const char *location)
{
	char  *path;
	GFile *file;

	if (!g_ascii_strncasecmp (location, "file:", strlen ("file:")))
		return g_file_new_for_uri (location);

	if (g_path_is_absolute (location))
		return g_file_new_for_path (location);

	path = panel_make_full_path (NULL, location);
	file = g_file_new_for_path (path);
	g_free (path);

	return file;
}

__create_base_blobdir(const gchar *path)
{
	if (path == NULL)
		return FALSE;

	if (g_str_equal(path, ""))
		return FALSE;

	if (g_file_test(path, G_FILE_TEST_EXISTS))
		return TRUE;

	gchar *dir_path = g_path_get_dirname(path);

	gint rv = g_mkdir_with_parents((const gchar *)dir_path, 0711);

	if (dir_path)
		g_free (dir_path);

	if (rv == -1)
		return FALSE;

	return TRUE;
}

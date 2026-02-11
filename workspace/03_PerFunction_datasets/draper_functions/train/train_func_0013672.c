add_template_dir (const char *path, GHashTable *h)
{
	GDir *dir;
	const char *name;

	dir = g_dir_open (path, 0, NULL);
	if (!dir)
		return;

	while ((name = g_dir_read_name (dir))) {
		char *fullname = g_build_filename (path, name, NULL);


		g_hash_table_remove (h, name);

		if (g_file_test (fullname, G_FILE_TEST_IS_REGULAR)) {
			char *uri = go_filename_to_uri (fullname);
			g_hash_table_insert (h, g_strdup (name), uri);
		}
		g_free (fullname);
	}
	g_dir_close (dir);
}

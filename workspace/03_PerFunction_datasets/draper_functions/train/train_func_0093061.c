nemo_create_templates_directory (void)
{
	char *dir;

	dir = nemo_get_templates_directory ();
	if (!g_file_test (dir, G_FILE_TEST_EXISTS)) {
		g_mkdir (dir, DEFAULT_NEMO_DIRECTORY_MODE);
	}
	g_free (dir);
}

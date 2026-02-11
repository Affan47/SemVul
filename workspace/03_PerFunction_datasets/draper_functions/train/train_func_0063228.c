in_vc_git(const gchar * filename)
{
	const gchar *argv[] = { "git", "ls-files", "--", NULL, NULL };
	gchar *dir;
	gchar *base_name;
	gboolean ret = FALSE;
	gchar *std_output;

	if (!find_dir(filename, ".git", TRUE))
		return FALSE;

	if (g_file_test(filename, G_FILE_TEST_IS_DIR))
		return TRUE;

	dir = g_path_get_dirname(filename);
	base_name = g_path_get_basename(filename);
	argv[3] = base_name;

	execute_custom_command(dir, (const gchar **) argv, NULL, &std_output, NULL,
			       dir, NULL, NULL);
	if (NZV(std_output))
	{
		ret = TRUE;
		g_free(std_output);
	}

	g_free(base_name);
	g_free(dir);

	return ret;
}

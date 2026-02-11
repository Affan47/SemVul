midgard_core_views_read_dir(const gchar *path)
{
	g_assert(path != NULL);

	const gchar *filename;
	GError *error;
	GDir *dir = g_dir_open(path, 0, &error);
	gchar *fullpath = NULL;

	if (!dir) {

		g_warning("Failed to read '%s' directory. %s",
				path, error && error->message ? error->message : "Error message not available");

		if (error)
			g_error_free(error);

		return;
	}

	do {
		filename = g_dir_read_name(dir);
		fullpath = g_build_path(G_DIR_SEPARATOR_S, path, filename, NULL);

		if (!g_file_test (fullpath, G_FILE_TEST_IS_DIR)
				&& g_file_test (fullpath, G_FILE_TEST_IS_REGULAR)
				&& g_str_has_suffix(filename, ".xml")){


			if (g_str_has_prefix(filename, ".")
					|| g_str_has_prefix(filename, "#")
					|| g_str_has_suffix(filename, "~")) {

				g_warning("File %s ignored!", filename);

			} else {

				parsed_view = fullpath;
				midgard_core_views_read_file(fullpath);
				parsed_view = NULL;
			}
		}

		g_free (fullpath);

	} while (filename != NULL);

	g_dir_close(dir);
}

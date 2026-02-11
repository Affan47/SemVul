acb_project_remove_all_files_with_prefix (const gchar *directory, const gchar *prefix)
{
	GDir *dir;
	GError *error = NULL;
	const gchar *filename;
	gchar *src;
	gint retval;


	dir = g_dir_open (directory, 0, &error);
	if (dir == NULL) {
		g_warning ("cannot open directory: %s", error->message);
		g_error_free (error);
		return;
	}


	while ((filename = g_dir_read_name (dir))) {
		if (!g_str_has_prefix (filename, prefix))
			continue;
		src = g_build_filename (directory, filename, NULL);
		retval = g_unlink (src);
		if (retval != 0)
			g_warning ("failed to delete %s", src);
		g_free (src);
	}
	g_dir_close (dir);
}

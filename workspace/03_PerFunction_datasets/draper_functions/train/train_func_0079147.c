ews_remove_attachments (const gchar *attachment_dir)
{
	GDir *dir;

	dir = g_dir_open (attachment_dir, 0, NULL);
	if (dir) {
		const gchar *fname;
		gchar *full_path;

		while ((fname = g_dir_read_name (dir))) {
			full_path = g_build_filename (attachment_dir, fname, NULL);
			if (g_unlink (full_path) != 0) {
				g_free (full_path);
				g_dir_close (dir);

				return FALSE;
			}

			g_free (full_path);
		}

		g_dir_close (dir);
	}

	return TRUE;
}

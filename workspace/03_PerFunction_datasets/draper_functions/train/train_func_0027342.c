tracker_db_manager_set_first_index_done (gboolean done)
{
	gboolean already_exists;
	gchar *filename;

	filename = get_first_index_filename ();
	already_exists = g_file_test (filename, G_FILE_TEST_EXISTS);

	if (done && !already_exists) {
		GError *error = NULL;


		if (!g_file_set_contents (filename, PACKAGE_VERSION, -1, &error)) {
			g_warning ("  Could not create file:'%s' failed, %s",
			           filename,
			           error->message);
			g_error_free (error);
		} else {
			g_message ("  First index file:'%s' created",
			           filename);
		}
	} else if (!done && already_exists) {

		g_message ("  Removing first index file:'%s'", filename);

		if (g_remove (filename)) {
			g_warning ("    Could not remove file:'%s', %s",
			           filename,
			           g_strerror (errno));
		}
	}

	g_free (filename);
}

check_file_cb (TrackerMinerFS *fs,
               GFile          *file,
               gpointer                user_data)
{
	gchar *path;
	gchar *basename;
	gboolean should_process;

	should_process = FALSE;
	basename = NULL;
	path = g_file_get_path (file);

	if (tracker_is_empty_string (path)) {
		goto done;
	}

	if (!g_utf8_validate (path, -1, NULL)) {
		g_message ("Ignoring path:'%s', not valid UTF-8", path);
		goto done;
	}


	basename = g_file_get_basename (file);

	if (!basename || basename[0] == '.') {
		goto done;
	}

	should_process = TRUE;

 done:
	g_free (path);
	g_free (basename);

	return should_process;
}

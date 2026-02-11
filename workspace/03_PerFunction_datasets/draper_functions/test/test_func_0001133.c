up_history_array_from_file (GPtrArray *list, const gchar *filename)
{
	gboolean ret;
	GError *error = NULL;
	gchar *data = NULL;
	gchar **parts = NULL;
	guint i;
	guint length;
	UpHistoryItem *item;


	ret = g_file_test (filename, G_FILE_TEST_EXISTS);
	if (!ret) {
		g_debug ("failed to get data from %s as file does not exist", filename);
		goto out;
	}


	ret = g_file_get_contents (filename, &data, NULL, &error);
	if (!ret) {
		g_warning ("failed to get data: %s", error->message);
		g_error_free (error);
		goto out;
	}


	parts = g_strsplit (data, "\n", 0);
	length = g_strv_length (parts);
	if (length == 0) {
		g_debug ("no data in %s", filename);
		goto out;
	}


	g_debug ("loading %i items of data from %s", length, filename);
	for (i=0; i<length-1; i++) {
		item = up_history_item_new ();
		ret = up_history_item_set_from_string (item, parts[i]);
		if (ret)
			g_ptr_array_add (list, item);
	}

out:
	g_strfreev (parts);
	g_free (data);
	return ret;
}

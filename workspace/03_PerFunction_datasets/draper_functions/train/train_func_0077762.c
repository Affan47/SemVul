pk_network_stack_unix_get_state (PkNetworkStack *nstack)
{
	gchar *contents = NULL;
	gboolean ret;
	GError *error = NULL;
	gchar **lines = NULL;
	guint number_lines;
	guint i;
	gboolean online = FALSE;
	PkNetworkEnum state = PK_NETWORK_ENUM_ONLINE;


	if (!g_file_test (PK_NETWORK_PROC_ROUTE, G_FILE_TEST_EXISTS)) {
		goto out;
	}


	ret = g_file_get_contents (PK_NETWORK_PROC_ROUTE, &contents, NULL, &error);
	if (!ret) {
		g_warning ("could not open %s: %s", PK_NETWORK_PROC_ROUTE, error->message);
		g_error_free (error);

		goto out;
	}


	if (contents == NULL) {
		g_warning ("insane contents of %s", PK_NETWORK_PROC_ROUTE);
		goto out;
	}


	lines = g_strsplit (contents, "\n", 0);
	if (lines == NULL) {
		g_warning ("unable to split %s", PK_NETWORK_PROC_ROUTE);
		goto out;
	}

	number_lines = g_strv_length (lines);
	for (i=0; i<number_lines; i++) {


		ret = pk_network_stack_unix_is_valid (lines[i]);
		if (ret)
			online = TRUE;
	}

	if (!online)
		state = PK_NETWORK_ENUM_OFFLINE;
out:
	g_free (contents);
	g_strfreev (lines);
	return state;
}

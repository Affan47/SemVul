context_init (gint    argc,
              gchar **argv)
{
	GOptionContext *context;
	gint n_remaining;
	gchar *file_path;
	GError *error = NULL;


	context = g_option_context_new ("- Simulate MTP daemon");
	g_option_context_add_main_entries (context, entries, NULL);
	g_option_context_parse (context, &argc, &argv, NULL);
	g_option_context_free (context);


	n_remaining = remaining ? g_strv_length (remaining) : 0;
	if (n_remaining != 2) {
		g_printerr ("You must provide FILE and DESTDIR\n");
		return FALSE;
	}


	file = g_file_new_for_commandline_arg (remaining[0]);
	file_uri = g_file_get_uri (file);
	file_path = g_file_get_path (file);
	if (g_file_query_file_type (file,
	                            G_FILE_QUERY_INFO_NONE,
	                            NULL) !=  G_FILE_TYPE_REGULAR) {
		g_printerr ("File '%s' is not a valid regular file\n",
		            file_uri);
		return FALSE;
	}


	destdir = g_file_new_for_commandline_arg (remaining[1]);
	destdir_uri = g_file_get_uri (destdir);
	if (g_file_query_file_type (destdir,
	                            G_FILE_QUERY_INFO_NONE,
	                            NULL) !=  G_FILE_TYPE_DIRECTORY) {
		g_printerr ("Destination path '%s' is not a valid directory\n",
		            destdir_uri);
		return FALSE;
	}


	if (n_copies == 0) {
		g_printerr ("Number of copies must be greater than 0\n");
		return FALSE;
	}


	if (copy_rate == 0) {
		g_printerr ("Copy rate must be greater than 0\n");
		return FALSE;
	}


	timeout_copy_rate = copy_rate * 1024.0 * COPY_TIMEOUT_MS / 1000.0;


	if (!g_file_get_contents (file_path,
	                          &buffer,
	                          &buffer_size,
	                          &error)) {
		g_error ("Couldn't load file '%s' contents: %s",
		         file_uri,
		         error ? error->message : "unknown error");
	}


	connection = tracker_sparql_connection_get (NULL, &error);
	if (!connection) {

		g_error ("Couldn't get sparql connection: %s",
		         error ? error->message : "unknown error");
	}

	g_print ("\
Simulating MTP daemon with:\n\
  * File:    %s (%" G_GSIZE_FORMAT " bytes)\n\
  * Destdir: %s\n\
  * Copies:  %d\n\
  * Rate:    %d KBytes/s (%d bytes every %d ms)\n\
  * Mode:    %s\n",
	         file_uri,
	         buffer_size,
	         destdir_uri,
	         n_copies,
	         copy_rate,
	         timeout_copy_rate,
	         COPY_TIMEOUT_MS,
	         use_batch ? "Hidden & Batch" : use_hidden ? "Hidden" : "Normal");

	return TRUE;
}

main (gint argc,
      gchar **argv)
{
	gchar * line = NULL;
	gsize len = 0;
	ECalBackendFile * cbfile;
	gint num = 0;
	GError *error = NULL;
	GOptionContext *context;
	FILE * fin = NULL;

	g_type_init ();

	context = g_option_context_new ("- test utility for e-d-s file backend");
	g_option_context_add_main_entries (context, entries, GETTEXT_PACKAGE);
	if (!g_option_context_parse (context, &argc, &argv, &error))
	{
		g_print ("option parsing failed: %s\n", error->message);
		exit (1);
	}

	calendar_fname = g_strdup ("calendar.ics");

	if (!calendar_fname)
	{
		g_message (G_STRLOC " Please, use -c parameter");
		exit (-1);
	}

	cbfile = g_object_new (E_TYPE_CAL_BACKEND_FILE, NULL);
	open_cal (cbfile, calendar_fname, &error);
	if (error != NULL) {
		g_message (G_STRLOC " Could not open calendar %s: %s", calendar_fname, error->message);
		exit (-1);
	}

	if (fname)
	{
		fin = fopen (fname, "r");

		if (!fin)
		{
			g_message (G_STRLOC " Could not open file %s", fname);
			goto err0;
		}
	}
	else
	{
		g_message (G_STRLOC " Reading from stdin");
		fin = stdin;
	}

	while (private_getline (&line, &len, fin) != -1) {
		g_print ("Query %d: %s", num++, line);

		if (only_execute)
			execute_query (cbfile, line);
		else
			test_query (cbfile, line);
	}

	if (line)
		free (line);

	if (fname)
		fclose (fin);

err0:
	g_object_unref (cbfile);

	return 0;
}

open_cl_files(gint argc, gchar **argv)
{
	gint i;

	for (i = 1; i < argc; i++)
	{
		gchar *filename = main_get_argv_filename(argv[i]);

		if (g_file_test(filename, G_FILE_TEST_IS_DIR))
		{
			g_free(filename);
			continue;
		}

#ifdef G_OS_WIN32

		SETPTR(filename, g_locale_to_utf8(filename, -1, NULL, NULL, NULL));
#endif
		if (filename && ! main_handle_filename(filename))
		{
			const gchar *msg = _("Could not find file '%s'.");

			g_printerr(msg, filename);
			g_printerr("\n");
			ui_set_statusbar(TRUE, msg, filename);
		}
		g_free(filename);
	}
}

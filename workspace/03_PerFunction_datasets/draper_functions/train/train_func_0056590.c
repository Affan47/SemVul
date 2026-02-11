send_open_command(gint sock, gint argc, gchar **argv)
{
	gint i;
	gchar *filename;

	g_return_if_fail(argc > 1);
	geany_debug("using running instance of Geany");

	if (cl_options.goto_line >= 0)
	{
		gchar *line = g_strdup_printf("%d\n", cl_options.goto_line);
		socket_fd_write_all(sock, "line\n", 5);
		socket_fd_write_all(sock, line, strlen(line));
		socket_fd_write_all(sock, ".\n", 2);
		g_free(line);
	}

	if (cl_options.goto_column >= 0)
	{
		gchar *col = g_strdup_printf("%d\n", cl_options.goto_column);
		socket_fd_write_all(sock, "column\n", 7);
		socket_fd_write_all(sock, col, strlen(col));
		socket_fd_write_all(sock, ".\n", 2);
		g_free(col);
	}

	if (cl_options.readonly)
		socket_fd_write_all(sock, "openro\n", 7);
	else
		socket_fd_write_all(sock, "open\n", 5);

	for (i = 1; i < argc && argv[i] != NULL; i++)
	{
		filename = main_get_argv_filename(argv[i]);


		if (filename != NULL)
		{
			socket_fd_write_all(sock, filename, strlen(filename));
			socket_fd_write_all(sock, "\n", 1);
		}
		else
		{
			g_printerr(_("Could not find file '%s'."), filename);
			g_printerr("\n");
		}
		g_free(filename);
	}
	socket_fd_write_all(sock, ".\n", 2);
}

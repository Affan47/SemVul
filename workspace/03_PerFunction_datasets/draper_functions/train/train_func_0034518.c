panel_run_dialog_prepend_terminal_to_vector (int *argc, char ***argv)
{
        char **real_argv;
        int real_argc;
        int i, j;
	char **term_argv = NULL;
	int term_argc = 0;
	GSettings *settings;

	gchar *terminal = NULL;

	char **the_argv;

        g_return_if_fail (argc != NULL);
        g_return_if_fail (argv != NULL);


        if(*argv == NULL)
                *argc = 0;

	the_argv = *argv;


	if (*argc < 0) {
		for (i = 0; the_argv[i] != NULL; i++)
			;
		*argc = i;
	}

	settings = g_settings_new ("org.gnome.desktop.default-applications.terminal");
	terminal = g_settings_get_string (settings, "exec");

	if (terminal) {
		gchar *command_line;
		gchar *exec_flag;

		exec_flag = g_settings_get_string (settings, "exec-arg");

		if (exec_flag == NULL)
			command_line = g_strdup (terminal);
		else
			command_line = g_strdup_printf ("%s %s", terminal,
							exec_flag);

		g_shell_parse_argv (command_line,
				    &term_argc,
				    &term_argv,
				    NULL );

		g_free (command_line);
		g_free (exec_flag);
		g_free (terminal);
	}

	g_object_unref (settings);

	if (term_argv == NULL) {
		char *check;

		term_argc = 2;
		term_argv = g_new0 (char *, 3);

		check = g_find_program_in_path ("gnome-terminal");
		if (check != NULL) {
			term_argv[0] = check;


			term_argv[1] = g_strdup ("-x");
		} else {
			if (check == NULL)
				check = g_find_program_in_path ("nxterm");
			if (check == NULL)
				check = g_find_program_in_path ("color-xterm");
			if (check == NULL)
				check = g_find_program_in_path ("rxvt");
			if (check == NULL)
				check = g_find_program_in_path ("xterm");
			if (check == NULL)
				check = g_find_program_in_path ("dtterm");
			if (check == NULL) {
				g_warning (_("Cannot find a terminal, using "
					     "xterm, even if it may not work"));
				check = g_strdup ("xterm");
			}
			term_argv[0] = check;
			term_argv[1] = g_strdup ("-e");
		}
	}

        real_argc = term_argc + *argc;
        real_argv = g_new (char *, real_argc + 1);

        for (i = 0; i < term_argc; i++)
                real_argv[i] = term_argv[i];

        for (j = 0; j < *argc; j++, i++)
                real_argv[i] = (char *)the_argv[j];

	real_argv[i] = NULL;

	g_free (*argv);
	*argv = real_argv;
	*argc = real_argc;


	g_free (term_argv);
}

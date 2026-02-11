finger_do (Netinfo * netinfo)
{
	GtkTextBuffer *buffer = NULL;
	GtkTextIter start, end;
	const gchar *host = NULL;
	const gchar *user = NULL;
	gchar *command = NULL;
	gchar *program = NULL;

	gchar **command_line;
	gchar **command_options;

	gint i, j, num_terms;
	gchar *command_arg = NULL;
	gboolean user_is_set, host_is_set;

	g_return_if_fail (netinfo != NULL);

	host = netinfo_get_host (netinfo);
	user = netinfo_get_user (netinfo);

	if (g_ascii_strcasecmp (user, "") != 0)
		netinfo->stbar_text =
			g_strdup_printf (_("Getting information of %s on \"%s\""), user,
					 g_ascii_strcasecmp (host, "") != 0 ? host : "localhost");
	else
		netinfo->stbar_text =
			g_strdup_printf (_("Getting information of all users on \"%s\""),
					 g_ascii_strcasecmp (host, "") != 0 ? host : "localhost");


	buffer =
		gtk_text_view_get_buffer (GTK_TEXT_VIEW (netinfo->output));

	gtk_text_buffer_get_bounds (buffer, &start, &end);
	gtk_text_buffer_delete (buffer, &start, &end);

	program = util_find_program_in_path ("finger", NULL);

	if (program == NULL) {
		program = util_find_program_dialog ("pinky", NULL);
	}

	if (program != NULL) {


		user_is_set = (strcmp (user, "") != 0);
		host_is_set = (strcmp (host, "") != 0);

		if (user_is_set && ! host_is_set) {
			command_arg = g_strdup (user);
		} else if (user_is_set && host_is_set) {
			command_arg = g_strdup_printf ("%s@%s", user, host);
		} else if (! user_is_set && host_is_set) {
			command_arg = g_strdup_printf ("@%s", host);
		}

		num_terms = 3;
		if (command_arg != NULL)
			num_terms++;

		command_options = g_strsplit (FINGER_OPTIONS, " ", -1);
		if (command_options != NULL) {
			for (j = 0; command_options[j] != NULL; j++)
				num_terms++;
		}
		command_line = g_new (gchar *, num_terms + 1);
		i = 0;
		command_line[i++] = g_strdup (program);
		command_line[i++] = g_strdup (program);
		if (command_options != NULL) {
			for (j = 0; command_options[j] != NULL; j++)
				command_line[i++] = g_strdup (command_options[j]);
		}
		if (command_arg != NULL)
			command_line[i++] = g_strdup (command_arg);
		command_line[i++] = NULL;

		g_strfreev (netinfo->command_line);
		netinfo->command_line = command_line;

		netinfo_process_command (netinfo);

		g_free (command_arg);
		g_strfreev (command_options);
	}

	g_free (command);
	g_free (program);
}

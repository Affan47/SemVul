panel_run_dialog_execute (PanelRunDialog *dialog)
{
	GError   *error;
	gboolean  result;
	char     *command;
	char     *disk;
	char     *scheme;

	command = g_strdup (panel_run_dialog_get_combo_text (dialog));
	command = g_strchug (command);

	if (!command || !command [0]) {
		g_free (command);
		return;
	}


	if (!strcmp (command, "free the fish")) {
		start_screen_check ();

		g_free (command);
		gtk_widget_destroy (dialog->run_dialog);
		return;
	}

	error = NULL;
	disk = g_locale_from_utf8 (command, -1, NULL, NULL, &error);

	if (!disk || error) {
		char *primary;

		primary = g_strdup_printf (_("Could not convert '%s' from UTF-8"),
					   command);
		panel_error_dialog (GTK_WINDOW (dialog->run_dialog), NULL,
				    "cannot_convert_command_from_utf8", TRUE,
				    primary, error->message);
		g_free (primary);

		g_error_free (error);
		return;
	}

	result = FALSE;

	scheme = g_uri_parse_scheme (disk);


	if (g_path_is_absolute (disk) || !scheme)
		result = panel_run_dialog_launch_command (dialog, command, disk);

	if (!result) {
		GFile     *file;
		char      *uri;
		GdkScreen *screen;

		file = panel_util_get_file_optional_homedir (command);
		uri = g_file_get_uri (file);
		g_object_unref (file);

		screen = gtk_window_get_screen (GTK_WINDOW (dialog->run_dialog));
		result = panel_show_uri (screen, uri,
					 gtk_get_current_event_time (), NULL);

		g_free (uri);
	}

	if (result) {

		_panel_run_save_recent_programs_list (dialog, command);


		gtk_widget_destroy (dialog->run_dialog);
	}

	g_free (command);
	g_free (disk);
	g_free (scheme);
}

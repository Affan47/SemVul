gedit_app_activate (GApplication *application)
{
	GeditWindow *window = NULL;
	GeditTab *tab;
	gboolean doc_created = FALSE;

	if (!new_window)
	{
		window = get_active_window (GTK_APPLICATION (application));
	}

	if (window == NULL)
	{
		gedit_debug_message (DEBUG_APP, "Create main window");
		window = gedit_app_create_window (GEDIT_APP (application), NULL);

		gedit_debug_message (DEBUG_APP, "Show window");
		gtk_widget_show (GTK_WIDGET (window));
	}

	if (geometry)
	{
		gtk_window_parse_geometry (GTK_WINDOW (window),
		                           geometry);
	}

	if (stdin_stream)
	{
		gedit_debug_message (DEBUG_APP, "Load stdin");

		tab = gedit_window_create_tab_from_stream (window,
		                                           stdin_stream,
		                                           encoding,
		                                           line_position,
		                                           column_position,
		                                           TRUE);
		doc_created = tab != NULL;

		if (doc_created && command_line)
		{
			set_command_line_wait (tab);
		}
		g_input_stream_close (stdin_stream, NULL, NULL);
	}

	if (file_list != NULL)
	{
		GSList *loaded;

		gedit_debug_message (DEBUG_APP, "Load files");
		loaded = _gedit_cmd_load_files_from_prompt (window,
		                                            file_list,
		                                            encoding,
		                                            line_position,
		                                            column_position);

		doc_created = doc_created || loaded != NULL;

		if (command_line)
		{
			g_slist_foreach (loaded, (GFunc)set_command_line_wait, NULL);
		}
		g_slist_free (loaded);
	}

	if (!doc_created || new_document)
	{
		gedit_debug_message (DEBUG_APP, "Create tab");
		tab = gedit_window_create_tab (window, TRUE);

		if (command_line)
		{
			set_command_line_wait (tab);
		}
	}

	gtk_window_present (GTK_WINDOW (window));
}

save_ui_prefs(GKeyFile *config)
{
	g_key_file_set_boolean(config, PACKAGE, "sidebar_visible", ui_prefs.sidebar_visible);
	g_key_file_set_boolean(config, PACKAGE, "statusbar_visible", interface_prefs.statusbar_visible);
	g_key_file_set_boolean(config, PACKAGE, "msgwindow_visible", ui_prefs.msgwindow_visible);
	g_key_file_set_boolean(config, PACKAGE, "fullscreen", ui_prefs.fullscreen);


	{
		GtkTextBuffer *buffer;
		GtkTextIter start, end, iter;
		GtkTextMark *mark;

		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(msgwindow.scribble));
		gtk_text_buffer_get_bounds(buffer, &start, &end);
		scribble_text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
		g_key_file_set_string(config, PACKAGE, "scribble_text", scribble_text);
		g_free(scribble_text);

		mark = gtk_text_buffer_get_insert(buffer);
		gtk_text_buffer_get_iter_at_mark(buffer, &iter, mark);
		scribble_pos = gtk_text_iter_get_offset(&iter);
		g_key_file_set_integer(config, PACKAGE, "scribble_pos", scribble_pos);
	}

	if (prefs.save_winpos)
	{
		GdkWindowState wstate;

		g_key_file_set_integer(config, PACKAGE, "treeview_position",
				gtk_paned_get_position(GTK_PANED(ui_lookup_widget(main_widgets.window, "hpaned1"))));
		g_key_file_set_integer(config, PACKAGE, "msgwindow_position",
				gtk_paned_get_position(GTK_PANED(ui_lookup_widget(main_widgets.window, "vpaned1"))));

		gtk_window_get_position(GTK_WINDOW(main_widgets.window), &ui_prefs.geometry[0], &ui_prefs.geometry[1]);
		gtk_window_get_size(GTK_WINDOW(main_widgets.window), &ui_prefs.geometry[2], &ui_prefs.geometry[3]);
		wstate = gdk_window_get_state(gtk_widget_get_window(main_widgets.window));
		ui_prefs.geometry[4] = (wstate & GDK_WINDOW_STATE_MAXIMIZED) ? 1 : 0;
		g_key_file_set_integer_list(config, PACKAGE, "geometry", ui_prefs.geometry, 5);
	}

	g_key_file_set_string(config, PACKAGE, "custom_date_format", ui_prefs.custom_date_format);
	if (ui_prefs.custom_commands != NULL)
	{
		g_key_file_set_string_list(config, PACKAGE, "custom_commands",
				(const gchar**) ui_prefs.custom_commands, g_strv_length(ui_prefs.custom_commands));
		g_key_file_set_string_list(config, PACKAGE, "custom_commands_labels",
				(const gchar**) ui_prefs.custom_commands_labels, g_strv_length(ui_prefs.custom_commands_labels));
	}
}

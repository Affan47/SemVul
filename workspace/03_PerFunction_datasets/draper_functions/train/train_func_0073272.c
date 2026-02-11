mg_create_tabwindow (session *sess)
{
	GtkWidget *win;
	GtkWidget *table;

	win = gtkutil_window_new ("HexChat", NULL, prefs.hex_gui_win_width,
									  prefs.hex_gui_win_height, 0);
	sess->gui->window = win;
	gtk_window_move (GTK_WINDOW (win), prefs.hex_gui_win_left,
						  prefs.hex_gui_win_top);
	if (prefs.hex_gui_win_state)
		gtk_window_maximize (GTK_WINDOW (win));
	gtk_container_set_border_width (GTK_CONTAINER (win), GUI_BORDER);

	g_signal_connect (G_OBJECT (win), "delete_event",
						   G_CALLBACK (mg_tabwindow_de_cb), 0);
	g_signal_connect (G_OBJECT (win), "destroy",
						   G_CALLBACK (mg_tabwindow_kill_cb), 0);
	g_signal_connect (G_OBJECT (win), "focus_in_event",
							G_CALLBACK (mg_tabwin_focus_cb), NULL);
	g_signal_connect (G_OBJECT (win), "configure_event",
							G_CALLBACK (mg_configure_cb), NULL);
	g_signal_connect (G_OBJECT (win), "window_state_event",
							G_CALLBACK (mg_windowstate_cb), NULL);

	palette_alloc (win);

	sess->gui->main_table = table = gtk_table_new (4, 3, FALSE);

	gtk_table_set_row_spacing (GTK_TABLE (table), 0, GUI_SPACING);

	gtk_table_set_col_spacing (GTK_TABLE (table), 0, 1);
	gtk_table_set_col_spacing (GTK_TABLE (table), 1, 1);
	gtk_container_add (GTK_CONTAINER (win), table);

	mg_create_irctab (sess, table);
	mg_create_tabs (sess->gui);
	mg_create_menu (sess->gui, table, sess->server->is_away);

	mg_focus (sess);

	gtk_widget_show_all (table);

	if (prefs.hex_gui_hide_menu)
		gtk_widget_hide (sess->gui->menu);

	mg_decide_userlist (sess, FALSE);

	if (!prefs.hex_gui_topicbar)
		gtk_widget_hide (sess->gui->topic_bar);

	if (!prefs.hex_gui_mode_buttons)
		gtk_widget_hide (sess->gui->topicbutton_box);

	if (!prefs.hex_gui_ulist_buttons)
		gtk_widget_hide (sess->gui->button_box);

	if (!prefs.hex_gui_input_nick)
		gtk_widget_hide (sess->gui->nick_box);

	mg_place_userlist_and_chanview (sess->gui);

	gtk_widget_show (win);
}

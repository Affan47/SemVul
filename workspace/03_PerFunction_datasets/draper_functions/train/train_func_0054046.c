configuration_apply_settings(void)
{
	if (scribble_text)
	{
		GtkTextIter iter;
		GtkTextBuffer *buffer =
			gtk_text_view_get_buffer(GTK_TEXT_VIEW(msgwindow.scribble));

		gtk_text_buffer_set_text(buffer, scribble_text, -1);
		gtk_text_buffer_get_iter_at_offset(buffer, &iter, scribble_pos);
		gtk_text_buffer_place_cursor(buffer, &iter);
	}
	g_free(scribble_text);


	if (prefs.save_winpos)
	{
		gtk_paned_set_position(GTK_PANED(ui_lookup_widget(main_widgets.window, "hpaned1")), hpan_position);
		gtk_paned_set_position(GTK_PANED(ui_lookup_widget(main_widgets.window, "vpaned1")), vpan_position);
	}


	if (ui_prefs.fullscreen)
	{
		gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(ui_lookup_widget(main_widgets.window, "menu_fullscreen1")), TRUE);
		ui_prefs.fullscreen = TRUE;
		ui_set_fullscreen();
	}

	msgwin_show_hide_tabs();
}

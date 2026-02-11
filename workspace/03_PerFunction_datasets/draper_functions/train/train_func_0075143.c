advanced_find_cb (GtkAction *action,
                  gpointer   user_data)
{
	GHexWindow *win = GHEX_WINDOW(user_data);
	if (!win->advanced_find_dialog)
		win->advanced_find_dialog = create_advanced_find_dialog(win);

	if(!gtk_widget_get_visible(win->advanced_find_dialog->window)) {
		gtk_window_set_position (GTK_WINDOW(win->advanced_find_dialog->window), GTK_WIN_POS_MOUSE);
		gtk_window_set_default(GTK_WINDOW(win->advanced_find_dialog->window),
							   win->advanced_find_dialog->f_close);
		gtk_widget_show(win->advanced_find_dialog->window);
	}
	raise_and_focus_widget(win->advanced_find_dialog->window);
}

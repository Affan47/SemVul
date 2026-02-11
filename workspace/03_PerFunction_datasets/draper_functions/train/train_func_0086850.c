layout_menu_info_pixel_cb(GtkToggleAction *action, gpointer data)
{
	LayoutWindow *lw = data;

	if (lw->options.show_info_pixel == gtk_toggle_action_get_active(action)) return;

	layout_exit_fullscreen(lw);
	layout_info_pixel_set(lw, !lw->options.show_info_pixel);
}

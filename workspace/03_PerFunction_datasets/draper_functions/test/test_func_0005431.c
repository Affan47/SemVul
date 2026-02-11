layout_menu_edit_cb(GtkAction *action, gpointer data)
{
	LayoutWindow *lw = data;
	const gchar *key = gtk_action_get_name(action);

	if (!editor_window_flag_set(key))
		layout_exit_fullscreen(lw);

	file_util_start_editor_from_filelist(key, layout_selection_list(lw), layout_get_path(lw), lw->window);
}

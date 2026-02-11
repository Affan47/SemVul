prefs_actions_duplicate_cb(gpointer gtk_action, gpointer data)
{
	gint row;

	row = gtkut_list_view_get_selected_row(actions.actions_list_view);
	if (row <= 0)
		return;

	modified_list = !prefs_actions_clist_set_row(-row-2);
}

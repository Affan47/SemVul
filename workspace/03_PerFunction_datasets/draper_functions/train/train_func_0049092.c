mg_tabwindow_de_cb (GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	GSList *list;
	session *sess;

	if (prefs.hex_gui_tray_close && !unity_mode () && tray_toggle_visibility (FALSE))
		return TRUE;


	list = sess_list;
	while (list)
	{
		sess = list->data;
		if (!sess->gui->is_tab)
			return FALSE;
		list = list->next;
	}

	mg_open_quit_dialog (TRUE);
	return TRUE;
}

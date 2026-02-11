main_window_toggle_work_offline (MainWindow *mainwin, gboolean offline,
					gboolean ask_sync)
{
	static gboolean switching = FALSE;

	if (switching)
		return;

	switching = TRUE;

	offline_ask_sync = ask_sync;
	if (offline)
		online_switch_clicked (GTK_BUTTON(mainwin->online_switch), mainwin);
	else
		online_switch_clicked (GTK_BUTTON(mainwin->offline_switch), mainwin);
	offline_ask_sync = TRUE;

	switching = FALSE;
}

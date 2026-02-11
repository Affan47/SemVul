next_history_cb(GtkAction *action, gpointer data)
{
	MainWindow *mainwin = (MainWindow *)data;
	MsgInfo *info = messageview_nav_get_next(mainwin->messageview);
	if (info) {
		if (info->folder != mainwin->summaryview->folder_item)
			folderview_select(mainwin->folderview, info->folder);
		summary_display_by_msgnum(mainwin->summaryview, info->msgnum);
		procmsg_msginfo_free(info);
		main_window_set_menu_sensitive(mainwindow_get_mainwindow());
		toolbar_main_set_sensitive(mainwindow_get_mainwindow());
	}
}

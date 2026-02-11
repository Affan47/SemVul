main_window_popup(MainWindow *mainwin)
{
	static gboolean first_start = TRUE;

	if (!gtk_widget_get_visible(GTK_WIDGET(mainwin->window)))
		main_window_show(mainwin);

	if (prefs_common.mainwin_maximised)
		gtk_window_maximize(GTK_WINDOW(mainwin->window));

	if (first_start) {
		first_start = FALSE;
	} else {
		gtkut_window_popup(mainwin->window);
	}

	if (prefs_common.layout_mode == SMALL_LAYOUT) {
		if (mainwin->in_folder) {
			mainwindow_enter_folder(mainwin);
		} else {
			mainwindow_exit_folder(mainwin);
		}
	}
	fix_folderview_scroll(mainwin);
}

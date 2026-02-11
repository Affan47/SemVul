app_exit_cb(GtkAction *action, gpointer data)
{
	MainWindow *mainwin = (MainWindow *)data;
	if (prefs_common.clean_on_exit) {
		if (!main_window_empty_trash(mainwin, prefs_common.ask_on_clean, TRUE))
			return;
	}

	if (prefs_common.confirm_on_exit) {
		if (alertpanel(_("Exit"), _("Exit Claws Mail?"),
			       GTK_STOCK_CANCEL, GTK_STOCK_QUIT,  NULL)
		    != G_ALERTALTERNATE)
			return;
		manage_window_focus_in(mainwin->window, NULL, NULL);
	}

	app_will_exit(NULL, mainwin);
}

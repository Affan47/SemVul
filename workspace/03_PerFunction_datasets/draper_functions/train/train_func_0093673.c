main_window_close_cb(GtkWidget *widget, GdkEventAny *event,
				 gpointer data)
{
	MainWindow *mainwin = (MainWindow *)data;
	gboolean close_allowed = TRUE;

	hooks_invoke(MAIN_WINDOW_CLOSE, &close_allowed);

	if (close_allowed && mainwin->lock_count == 0)
		app_exit_cb(NULL, data);

	return TRUE;
}

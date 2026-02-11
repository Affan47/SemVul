ok_button_clicked(GtkButton *button, gpointer user_data)
{
	PrefsWindow *prefswindow = (PrefsWindow *) user_data;

	if (query_can_close_all_pages(prefswindow->prefs_pages)) {
		save_all_pages(prefswindow->prefs_pages);
		close_prefs_window(prefswindow);
	}
}

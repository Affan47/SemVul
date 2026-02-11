init_scopes_window(GtkWidget *main_window)
{
	scopes_window = create_scopes_window();


	pthread_mutex_init(&sl_mutex, (pthread_mutexattr_t *)NULL);

	if (prefs_get_bool(ap_prefs, "gtk2_interface", "scopeswindow_active", 0)) {
		gtk_widget_show_all(scopes_window);
	}

	return scopes_window;
}

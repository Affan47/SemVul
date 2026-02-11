ssl_manager_open(MainWindow *mainwin)
{
	if (!manager.window)
		ssl_manager_create();

	manage_window_set_transient(GTK_WINDOW(manager.window));
	gtk_widget_grab_focus(manager.close_btn);

	ssl_manager_load_certs();

	gtk_widget_show(manager.window);

}

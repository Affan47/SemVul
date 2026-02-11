send_progress_dialog_create(void)
{
	SendProgressDialog *dialog;
	ProgressDialog *progress;
	static GdkGeometry geometry;

	dialog = g_new0(SendProgressDialog, 1);

	progress = progress_dialog_create();
	gtk_window_set_title(GTK_WINDOW(progress->window),
			     _("Sending message"));
	g_signal_connect(G_OBJECT(progress->showlog_btn), "clicked",
			 G_CALLBACK(send_showlog_button_cb), dialog);
	g_signal_connect(G_OBJECT(progress->cancel_btn), "clicked",
			 G_CALLBACK(send_cancel_button_cb), dialog);
	g_signal_connect(G_OBJECT(progress->window), "delete_event",
			 G_CALLBACK(gtk_true), NULL);
	gtk_window_set_modal(GTK_WINDOW(progress->window), TRUE);
	g_signal_connect(G_OBJECT(progress->window), "size_allocate",
			 G_CALLBACK(send_progress_dialog_size_allocate_cb), NULL);
	manage_window_set_transient(GTK_WINDOW(progress->window));

	progress_dialog_get_fraction(progress);

	if (!geometry.min_height) {
		geometry.min_width = 460;
		geometry.min_height = 250;
	}

	gtk_window_set_geometry_hints(GTK_WINDOW(progress->window), NULL, &geometry,
				      GDK_HINT_MIN_SIZE);
	gtk_widget_set_size_request(progress->window, prefs_common.sendwin_width,
				    prefs_common.sendwin_height);

	if (!prefs_common.send_dialog_invisible) {
		gtk_widget_show_now(progress->window);
	}

	dialog->dialog = progress;

	return dialog;
}

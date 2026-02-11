send_key_events_window_main (gchar** args, int args_length1) {
	gint result = 0;
	SendKeyEventsWindow* window = NULL;
	SendKeyEventsWindow* _tmp0_ = NULL;
	setlocale (LC_ALL, "");
	gtk_init (&args_length1, &args);
	_tmp0_ = send_key_events_window_new ();
	g_object_ref_sink (_tmp0_);
	window = _tmp0_;
	g_signal_connect ((GtkWidget*) window, "destroy", (GCallback) _gtk_main_quit_gtk_widget_destroy, NULL);
	gtk_widget_show_all ((GtkWidget*) window);
	send_key_events_window_run_ibus_engine (window);
	gtk_main ();
	result = 0;
	_g_object_unref0 (window);
	return result;
}

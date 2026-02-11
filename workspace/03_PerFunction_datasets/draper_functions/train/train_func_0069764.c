stop_spinner (NautilusPropertiesWindow *window)
{
	gtk_spinner_stop (GTK_SPINNER (window->details->directory_contents_spinner));
	gtk_widget_hide (window->details->directory_contents_spinner);
	if (window->details->deep_count_spinner_timeout_id > 0) {
		g_source_remove (window->details->deep_count_spinner_timeout_id);
		window->details->deep_count_spinner_timeout_id = 0;
	}
}

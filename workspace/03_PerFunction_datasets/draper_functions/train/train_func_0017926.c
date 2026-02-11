stop_deep_count_for_file (NautilusPropertiesWindow *window,
			  NautilusFile             *file)
{
	if (g_list_find (window->details->deep_count_files, file)) {
		g_signal_handlers_disconnect_by_func (file,
						      G_CALLBACK (schedule_directory_contents_update),
						      window);
		nautilus_file_unref (file);
		window->details->deep_count_files = g_list_remove (window->details->deep_count_files, file);
	}
}

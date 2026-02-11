update_files_callback (gpointer data)
{
 	NautilusPropertiesWindow *window;

 	window = NAUTILUS_PROPERTIES_WINDOW (data);

	window->details->update_files_timeout_id = 0;

	properties_window_update (window, window->details->changed_files);

	if (window->details->original_files == NULL) {

		gtk_widget_destroy (GTK_WIDGET (window));
	} else {
		nautilus_file_list_free (window->details->changed_files);
		window->details->changed_files = NULL;
	}

 	return FALSE;
 }

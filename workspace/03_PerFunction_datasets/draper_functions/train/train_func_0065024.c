finish_loading (NautilusView *view)
{
	NautilusFileAttributes attributes;

	nautilus_profile_start (NULL);


	nautilus_profile_start ("BEGIN_LOADING");
	g_signal_emit (view, signals[BEGIN_LOADING], 0);
	nautilus_profile_end ("BEGIN_LOADING");


	nautilus_window_view_visible  (nautilus_view_get_window (view), NAUTILUS_VIEW (view));

	if (nautilus_directory_are_all_files_seen (view->details->model)) {


		unschedule_display_of_pending_files (view);
		schedule_timeout_display_of_pending_files (view, UPDATE_INTERVAL_MIN);
	}


	view->details->done_loading_handler_id = g_signal_connect
		(view->details->model, "done-loading",
		 G_CALLBACK (done_loading_callback), view);
	view->details->load_error_handler_id = g_signal_connect
		(view->details->model, "load-error",
		 G_CALLBACK (load_error_callback), view);


	attributes =
		NAUTILUS_FILE_ATTRIBUTES_FOR_ICON |
		NAUTILUS_FILE_ATTRIBUTE_DIRECTORY_ITEM_COUNT |
		NAUTILUS_FILE_ATTRIBUTE_INFO |
		NAUTILUS_FILE_ATTRIBUTE_LINK_INFO |
		NAUTILUS_FILE_ATTRIBUTE_MOUNT |
		NAUTILUS_FILE_ATTRIBUTE_EXTENSION_INFO;

	nautilus_directory_file_monitor_add (view->details->model,
					     &view->details->model,
					     view->details->show_hidden_files,
					     attributes,
					     files_added_callback, view);

    	view->details->files_added_handler_id = g_signal_connect
		(view->details->model, "files-added",
		 G_CALLBACK (files_added_callback), view);
	view->details->files_changed_handler_id = g_signal_connect
		(view->details->model, "files-changed",
		 G_CALLBACK (files_changed_callback), view);

	nautilus_profile_end (NULL);
}

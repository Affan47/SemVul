nemo_view_destroy (GtkWidget *object)
{
	NemoView *view;
	GList *node, *next;

	view = NEMO_VIEW (object);

	disconnect_model_handlers (view);

    if (view->details->bookmarks_changed_id != 0) {
        g_signal_handler_disconnect (view->details->bookmarks,
                         view->details->bookmarks_changed_id);
        view->details->bookmarks_changed_id = 0;
    }
    g_clear_object (&view->details->bookmarks);

	nemo_view_unmerge_menus (view);


	view->details->slot = NULL;
	view->details->window = NULL;

	nemo_view_stop_loading (view);

	for (node = view->details->scripts_directory_list; node != NULL; node = next) {
		next = node->next;
		remove_directory_from_scripts_directory_list (view, node->data);
	}

	for (node = view->details->templates_directory_list; node != NULL; node = next) {
		next = node->next;
		remove_directory_from_templates_directory_list (view, node->data);
	}

	while (view->details->subdirectory_list != NULL) {
		nemo_view_remove_subdirectory (view,
						   view->details->subdirectory_list->data);
	}

	remove_update_menus_timeout_callback (view);
	remove_update_status_idle_callback (view);

	if (view->details->display_selection_idle_id != 0) {
		g_source_remove (view->details->display_selection_idle_id);
		view->details->display_selection_idle_id = 0;
	}

	if (view->details->reveal_selection_idle_id != 0) {
		g_source_remove (view->details->reveal_selection_idle_id);
		view->details->reveal_selection_idle_id = 0;
	}

	if (view->details->delayed_rename_file_id != 0) {
		g_source_remove (view->details->delayed_rename_file_id);
		view->details->delayed_rename_file_id = 0;
	}

	if (view->details->model) {
		nemo_directory_unref (view->details->model);
		view->details->model = NULL;
	}

	if (view->details->directory_as_file) {
		nemo_file_unref (view->details->directory_as_file);
		view->details->directory_as_file = NULL;
	}

	GTK_WIDGET_CLASS (nemo_view_parent_class)->destroy (object);
}

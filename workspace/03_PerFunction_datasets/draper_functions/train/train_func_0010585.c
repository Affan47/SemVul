update_extra_viewer_in_view_as_menus (NemoWindow *window,
				      const char *id)
{
	gboolean had_extra_viewer;

	had_extra_viewer = window->details->extra_viewer != NULL;

	if (id == NULL) {
		if (!had_extra_viewer) {
			return;
		}
	} else {
		if (had_extra_viewer
		    && strcmp (window->details->extra_viewer, id) == 0) {
			return;
		}
	}
	g_free (window->details->extra_viewer);
	window->details->extra_viewer = g_strdup (id);

	if (window->details->extra_viewer_merge_id != 0) {
		gtk_ui_manager_remove_ui (window->details->ui_manager,
					  window->details->extra_viewer_merge_id);
		window->details->extra_viewer_merge_id = 0;
	}

	if (window->details->extra_viewer_radio_action != NULL) {
		gtk_action_group_remove_action (window->details->view_as_action_group,
						GTK_ACTION (window->details->extra_viewer_radio_action));
		window->details->extra_viewer_radio_action = NULL;
	}

	if (id != NULL) {
		window->details->extra_viewer_merge_id = gtk_ui_manager_new_merge_id (window->details->ui_manager);
                window->details->extra_viewer_radio_action =
			add_view_as_menu_item (window,
					       NEMO_MENU_PATH_EXTRA_VIEWER_PLACEHOLDER,
					       window->details->extra_viewer,
					       0,
					       window->details->extra_viewer_merge_id);
	}
}

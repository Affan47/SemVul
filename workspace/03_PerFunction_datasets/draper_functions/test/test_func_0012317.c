permission_button_update (NemoPropertiesWindow *window,
			  GtkToggleButton *button)
{
	GList *l;
	gboolean all_set;
	gboolean all_unset;
	gboolean all_cannot_set;
	gboolean is_folder, is_special;
	gboolean no_match;
	gboolean sensitive;
	guint32 button_permission;

	if (gtk_toggle_button_get_inconsistent (button) &&
	    window->details->has_recursive_apply) {


		return;
	}

	button_permission = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (button),
								"permission"));
	is_folder = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (button),
							"is-folder"));
	is_special = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (button),
							 "is-special"));

	all_set = TRUE;
	all_unset = TRUE;
	all_cannot_set = TRUE;
	no_match = TRUE;
	for (l = window->details->target_files; l != NULL; l = l->next) {
		NemoFile *file;
		guint32 file_permissions;

		file = NEMO_FILE (l->data);

		if (!nemo_file_can_get_permissions (file)) {
			continue;
		}

		if (!is_special &&
		    ((nemo_file_is_directory (file) && !is_folder) ||
		     (!nemo_file_is_directory (file) && is_folder))) {
			continue;
		}

		no_match = FALSE;

		file_permissions = nemo_file_get_permissions (file);

		if ((file_permissions & button_permission) == button_permission) {
			all_unset = FALSE;
		} else if ((file_permissions & button_permission) == 0) {
			all_set = FALSE;
		} else {
			all_unset = FALSE;
			all_set = FALSE;
		}

		if (nemo_file_can_set_permissions (file)) {
			all_cannot_set = FALSE;
		}
	}

	sensitive = !all_cannot_set;
	if (!is_folder) {

		sensitive |= window->details->has_recursive_apply;
	}


	g_signal_handlers_block_by_func (G_OBJECT (button),
					 G_CALLBACK (permission_button_toggled),
					 window);

	gtk_toggle_button_set_active (button, !all_unset);


	gtk_toggle_button_set_inconsistent (button,
					    (!all_unset && !all_set) ||
					    (!is_folder && no_match));
	gtk_widget_set_sensitive (GTK_WIDGET (button), sensitive);

	g_signal_handlers_unblock_by_func (G_OBJECT (button),
					   G_CALLBACK (permission_button_toggled),
					   window);
}

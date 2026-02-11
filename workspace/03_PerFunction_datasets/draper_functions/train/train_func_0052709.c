ok_button_clicked__step2 (GError   *error,
			  gpointer  user_data)
{
	DialogData  *data = user_data;
	GtkTreeIter  iter;
	GList       *old_files;
	GList       *new_files;
	GList       *scan1;
	GList       *scan2;
	GthTask     *task;

	if (error != NULL) {
		_gtk_error_dialog_from_gerror_show (GTK_WINDOW (data->dialog), _("Could not rename the files"), error);
		return;
	}


	if (data->file_list->next != NULL)
		g_settings_set_string (data->settings, PREF_RENAME_SERIES_TEMPLATE, gtk_entry_get_text (GTK_ENTRY (GET_WIDGET ("template_entry"))));

	g_settings_set_int (data->settings, PREF_RENAME_SERIES_START_AT, gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (GET_WIDGET ("start_at_spinbutton"))));

	if (gtk_combo_box_get_active_iter (GTK_COMBO_BOX (data->sort_combobox), &iter)) {
		GthFileDataSort *sort_type;

		gtk_tree_model_get (GTK_TREE_MODEL (data->sort_model),
				    &iter,
				    SORT_DATA_COLUMN, &sort_type,
				    -1);
		g_settings_set_string (data->settings, PREF_RENAME_SERIES_SORT_BY, sort_type->name);
	}

	g_settings_set_boolean (data->settings, PREF_RENAME_SERIES_REVERSE_ORDER, gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (GET_WIDGET ("reverse_order_checkbutton"))));
	g_settings_set_enum (data->settings, PREF_RENAME_SERIES_CHANGE_CASE, gtk_combo_box_get_active (GTK_COMBO_BOX (data->change_case_combobox)));


	old_files = NULL;
	new_files = NULL;

	for (scan1 = data->new_file_list, scan2 = data->new_names_list;
	     scan1 && scan2;
	     scan1 = scan1->next, scan2 = scan2->next)
	{
		GthFileData *file_data = scan1->data;
		char        *new_name  = scan2->data;
		GFile       *parent;
		GFile       *new_file;

		parent = g_file_get_parent (file_data->file);
		new_file = g_file_get_child (parent, new_name);

		old_files = g_list_prepend (old_files, g_object_ref (file_data->file));
		new_files = g_list_prepend (new_files, new_file);

		g_object_unref (parent);
	}
	old_files = g_list_reverse (old_files);
	new_files = g_list_reverse (new_files);

	task = gth_rename_task_new (old_files, new_files);
	gth_browser_exec_task (data->browser, task, FALSE);

	g_object_unref (task);
	destroy_dialog (data);
}

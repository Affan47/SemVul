gth_import_preferences_dialog_get_destination_example (GthImportPreferencesDialog *self)
{
	GFile              *destination;
	GthSubfolderType    subfolder_type;
	GthSubfolderFormat  subfolder_format;
	gboolean            single_subfolder;
	const char         *custom_format;
	GthFileData        *example_data;
	GTimeVal            timeval;
	GFile              *destination_example;

	destination = gth_import_preferences_dialog_get_destination (self);
	if (destination == NULL)
		return NULL;

	subfolder_type = get_subfolder_type (self);
	subfolder_format = gtk_combo_box_get_active (GTK_COMBO_BOX (self->priv->subfolder_format_list));
	single_subfolder = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (GET_WIDGET ("single_subfolder_checkbutton")));
	custom_format = gtk_entry_get_text (GTK_ENTRY (GET_WIDGET ("custom_format_entry")));

	example_data = create_example_file_data ();
	g_get_current_time (&timeval);

	destination_example = gth_import_utils_get_file_destination (example_data,
								     destination,
								     subfolder_type,
								     subfolder_format,
								     single_subfolder,
								     custom_format,
								     self->priv->event,
								     timeval);

	g_object_unref (example_data);
	g_object_unref (destination);

	return destination_example;
}

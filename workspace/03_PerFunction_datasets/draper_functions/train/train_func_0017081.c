project_setup_prefs(void)
{
	GtkWidget *path_entry = ui_lookup_widget(ui_widgets.prefs_dialog, "project_file_path_entry");
	GtkWidget *path_btn = ui_lookup_widget(ui_widgets.prefs_dialog, "project_file_path_button");
	static gboolean callback_setup = FALSE;

	g_return_if_fail(local_prefs.project_file_path != NULL);

	gtk_entry_set_text(GTK_ENTRY(path_entry), local_prefs.project_file_path);
	if (! callback_setup)
	{
		callback_setup = TRUE;
		ui_setup_open_button_callback(path_btn, NULL,
			GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, GTK_ENTRY(path_entry));
	}
}

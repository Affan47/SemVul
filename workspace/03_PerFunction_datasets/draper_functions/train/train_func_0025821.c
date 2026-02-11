share_settings_set_path (const gchar *path)
{
	GtkWidget *path_entry = gst_dialog_get_widget (tool->main_dialog, "share_path");
	GtkWidget *path_label = gst_dialog_get_widget (tool->main_dialog, "share_path_label");

	if (!path) {
		gtk_widget_show (path_entry);
		gtk_widget_hide (path_label);
	} else {
		gtk_widget_hide (path_entry);
		gtk_widget_show (path_label);
		gtk_label_set_text (GTK_LABEL (path_label), path);
		gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (path_entry), path);
	}
}

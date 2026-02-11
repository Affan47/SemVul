savefile_dialog_destroy(struct SaveFileDialog* dialog)
{
	char* path;
	path = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(dialog->filepath));
	if (dialog->respcode == GTK_RESPONSE_OK)
		config_set_lastsavedir(path);
	g_free(path);
	gtk_widget_destroy(dialog->dialogbox);

	g_free(dialog);
}

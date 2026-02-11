ay_do_file_selection_open(const char *inDefaultFile,
	const char *inWindowTitle, t_file_selection_callback *inCallback,
	void *inData)
{
	const char *selected_file = NULL;
	GtkWidget *dialog = NULL;

	dialog = gtk_file_chooser_dialog_new(inWindowTitle, NULL,
		GTK_FILE_CHOOSER_ACTION_OPEN,
		GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
		GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);

	if (inDefaultFile)
		gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(dialog),
			inDefaultFile);

	if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
		selected_file =
			gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
	else
		selected_file = NULL;

	(inCallback) (selected_file, inData);
	gtk_widget_destroy(dialog);
}

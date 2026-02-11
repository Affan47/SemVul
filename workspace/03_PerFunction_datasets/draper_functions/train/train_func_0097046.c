destination_button_clicked_cb(GtkWidget *button, gpointer data)
{
	if (rec_settings.destination)
		g_free(rec_settings.destination);

	rec_settings.destination = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));
}

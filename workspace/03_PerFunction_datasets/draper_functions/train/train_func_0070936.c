private_key_picker_file_set_cb (GtkWidget *chooser, gpointer user_data)
{
	EAPMethod *parent = (EAPMethod *) user_data;
	char *filename;

	filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (chooser));
	if (filename)
		private_key_picker_helper (parent, filename, TRUE);
	g_free (filename);
}

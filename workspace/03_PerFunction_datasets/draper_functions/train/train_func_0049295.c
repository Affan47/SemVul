update_preview_cb (GtkFileChooser *file_chooser,
                   gpointer data)
{
	GtkWidget *preview;
	gchar *filename = NULL;
	GdkPixbuf *pixbuf;

	gtk_file_chooser_set_preview_widget_active (file_chooser, FALSE);
	gtk_image_clear (GTK_IMAGE (data));
	preview = GTK_WIDGET (data);
	filename = gtk_file_chooser_get_preview_filename (file_chooser);
	if (filename == NULL)
		return;

	pixbuf = gdk_pixbuf_new_from_file_at_size (filename, 128, 128, NULL);
	g_free (filename);
	if (!pixbuf)
		return;

	gtk_file_chooser_set_preview_widget_active (file_chooser, TRUE);
	gtk_image_set_from_pixbuf (GTK_IMAGE (preview), pixbuf);
	g_object_unref (pixbuf);
}

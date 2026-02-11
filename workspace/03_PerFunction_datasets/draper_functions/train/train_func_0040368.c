GUI_update_preview (GtkWidget *widget,
					gpointer data)
{
	GtkWidget *preview;
	char *filename;
	gboolean have_preview = false;
	preview = GTK_WIDGET (data);
	if (preview_animation == 0)
		preview_animation = new GtkImageAnimation (GTK_IMAGE (preview));
	preview_animation->attach (GTK_IMAGE (preview));
	filename = gtk_file_chooser_get_preview_filename (GTK_FILE_CHOOSER(widget));
	if (filename) {
		have_preview = 	preview_animation->open (filename);
		g_free (filename);
	}
	else
		have_preview = false;
	if (have_preview)
		preview_animation->start();
	gtk_file_chooser_set_preview_widget_active (GTK_FILE_CHOOSER(widget), have_preview);
}

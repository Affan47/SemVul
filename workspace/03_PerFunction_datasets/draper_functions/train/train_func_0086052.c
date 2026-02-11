filesel_ok(GtkWidget *widget, GtkFileSelection *fs)
{
	gchar *dir;
	gchar *text;
	GtkTextBuffer *buffer;
	GtkTextIter start, end;

	LOG(LOG_DEBUG, "IN : filesel_ok()");

	dir = (gchar *)gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs));
	strcpy(last_dir, dir);
	dir = fs_to_unicode(dir);

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(dirgroup_view));
	gtk_text_buffer_get_bounds (buffer, &start, &end);
	text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
	if(strlen(text) != 0)
		gtk_text_buffer_insert(buffer, &end, "\n", 1);
	gtk_text_buffer_insert(buffer, &end, dir, strlen(dir));

	g_free(text);
	g_free(dir);

	gtk_grab_remove(GTK_WIDGET(fs));
	gtk_widget_destroy(GTK_WIDGET(fs));

	LOG(LOG_DEBUG, "OUT : filesel_ok()");
}

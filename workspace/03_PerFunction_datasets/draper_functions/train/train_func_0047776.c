gabedit_file_chooser_set_filter(GabeditFileChooser *fileChooser, const gchar *pattern)
{
	GtkFileFilter *filter;

	g_return_if_fail (fileChooser != NULL);
	g_return_if_fail (GABEDIT_IS_FILE_CHOOSER(fileChooser));
	g_return_if_fail (pattern != NULL);

	filter = gtk_file_filter_new ();
	gtk_file_filter_set_name (filter, pattern);
	gtk_file_filter_add_pattern (filter, pattern);
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (fileChooser), filter);
	gtk_file_chooser_set_filter (GTK_FILE_CHOOSER (fileChooser), filter);
}

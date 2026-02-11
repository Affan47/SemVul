eog_file_chooser_add_filter (EogFileChooser *chooser)
{
	GSList *it;
 	GtkFileFilter *all_file_filter;
	GtkFileFilter *all_img_filter;
	GSList *filters = NULL;
	GtkFileChooserAction action;

	action = gtk_file_chooser_get_action (GTK_FILE_CHOOSER (chooser));

	if (action != GTK_FILE_CHOOSER_ACTION_SAVE && action != GTK_FILE_CHOOSER_ACTION_OPEN) {
		return;
	}


	all_file_filter = gtk_file_filter_new ();
	gtk_file_filter_set_name (all_file_filter, _("All files"));
	gtk_file_filter_add_pattern (all_file_filter, "*");


	all_img_filter = gtk_file_filter_new ();
	gtk_file_filter_set_name (all_img_filter, _("Supported image files"));

	if (action == GTK_FILE_CHOOSER_ACTION_SAVE) {
		filters = _eog_file_chooser_prepare_save_file_filter(all_img_filter);
	}
	else {
		gtk_file_filter_add_pixbuf_formats(all_img_filter);
	}


	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (chooser), all_file_filter);
	gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (chooser), all_img_filter);
	gtk_file_chooser_set_filter (GTK_FILE_CHOOSER (chooser), all_img_filter);

	for (it = filters; it != NULL; it = it->next) {
		gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (chooser), GTK_FILE_FILTER (it->data));
	}
	g_slist_free (filters);
}

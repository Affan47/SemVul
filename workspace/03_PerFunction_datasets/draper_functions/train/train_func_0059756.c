show_file_selector_cb (GtkAction * action,
                       gpointer data)
{
	GSearchWindow * gsearch = data;
	GtkWidget * file_chooser;

	file_chooser = gtk_file_chooser_dialog_new (_("Save Search Results As..."),
	                                            GTK_WINDOW (gsearch->window),
	                                            GTK_FILE_CHOOSER_ACTION_SAVE,
	                                            GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
	                                            GTK_STOCK_SAVE, GTK_RESPONSE_OK,
	                                            NULL);

#if GTK_CHECK_VERSION(2,7,3)
	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (file_chooser), TRUE);
#endif
	if (gsearch->save_results_as_default_filename != NULL) {
		gtk_file_chooser_set_filename (GTK_FILE_CHOOSER (file_chooser),
		                               gsearch->save_results_as_default_filename);
	}

	g_signal_connect (G_OBJECT (file_chooser), "response",
			  G_CALLBACK (save_results_cb), gsearch);

	gtk_window_set_modal (GTK_WINDOW (file_chooser), TRUE);
	gtk_window_set_position (GTK_WINDOW (file_chooser), GTK_WIN_POS_CENTER_ON_PARENT);

	gtk_widget_show (GTK_WIDGET (file_chooser));
}

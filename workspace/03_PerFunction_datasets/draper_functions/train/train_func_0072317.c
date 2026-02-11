on_cvs_log_response(GtkDialog* dialog, gint response, CVSData* data)
{
	if (is_busy(data->plugin, dialog))
		return;

	switch (response)
	{
	case GTK_RESPONSE_OK:
	{
		const gchar* filename;
		GtkWidget* norecurse;
		GtkWidget* verbose;
		GtkWidget* fileentry;

		norecurse = GTK_WIDGET(gtk_builder_get_object(data->bxml, "cvs_logdialog_norecurse"));
		verbose = GTK_WIDGET(gtk_builder_get_object(data->bxml, "cvs_logdialog_verbose"));

		fileentry = GTK_WIDGET(gtk_builder_get_object(data->bxml, "cvs_logdialog_filename"));
		filename = gtk_entry_get_text(GTK_ENTRY(fileentry));
		if (!check_filename(dialog, filename))
			break;

		anjuta_cvs_log(ANJUTA_PLUGIN(data->plugin), filename,
			!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(norecurse)),
			gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(verbose)), NULL);


		cvs_data_free(data);
		gtk_widget_destroy (GTK_WIDGET(dialog));
		break;
		}
	default:
		cvs_data_free(data);
		gtk_widget_destroy (GTK_WIDGET(dialog));
		break;
	}
}

on_select_output_file_clicked(GtkWidget *widget, AnimationRenderUi *self) {
    GtkWidget *dialog;

#if (GTK_CHECK_VERSION(2, 4, 0))
    dialog = gtk_file_chooser_dialog_new ("Select Output File",
		                          GTK_WINDOW (glade_xml_get_widget (self->xml, "window")),
		                          GTK_FILE_CHOOSER_ACTION_SAVE,
					  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					  GTK_STOCK_OK, GTK_RESPONSE_OK,
					  NULL);
    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_OK) {
	    gchar *filename;
	    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
	    gtk_entry_set_text (GTK_ENTRY (glade_xml_get_widget (self->xml, "output_file")), filename);
	    g_free (filename);
    }
#else
    dialog = gtk_file_selection_new ("Select Output File");
    gtk_file_selection_set_filename (GTK_FILE_SELECTION (dialog),
				     gtk_entry_get_text (GTK_ENTRY (glade_xml_get_widget (self->xml, "output_file"))));

    if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_OK) {
	gtk_entry_set_text (GTK_ENTRY (glade_xml_get_widget (self->xml, "output_file")),
			    gtk_file_selection_get_filename (GTK_FILE_SELECTION (dialog)));
    }
#endif
    gtk_widget_destroy (dialog);
}

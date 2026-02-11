__ca_export_pkcs12 (GtkTreeIter *iter, gint type)
{
	GObject *widget = NULL;
	gchar * filename = NULL;
	GtkDialog * dialog = NULL;
	gint id;

        gchar *error_msg = NULL;

	widget = gtk_builder_get_object (main_window_gtkb, "main_window1");

	dialog = GTK_DIALOG (gtk_file_chooser_dialog_new
			       (_("Export whole certificate in PKCS#12 package"),
				GTK_WINDOW(widget),
				GTK_FILE_CHOOSER_ACTION_SAVE,
				GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
				GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
				NULL));

	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);

	if (gtk_dialog_run (GTK_DIALOG (dialog)) != GTK_RESPONSE_ACCEPT) {
		gtk_widget_destroy (GTK_WIDGET(dialog));
		return;
	}

	filename = g_strdup(gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog)));
	gtk_widget_destroy (GTK_WIDGET(dialog));
	gtk_tree_model_get(GTK_TREE_MODEL(ca_model), iter, CA_MODEL_COLUMN_ID, &id, -1);

        error_msg = export_pkcs12 (id, type, filename);

        g_free (filename);

        if (error_msg && strlen(error_msg)) {
                dialog_error (error_msg);
                return;
        }

        if (error_msg) {

                return;
        }


        dialog = GTK_DIALOG(gtk_message_dialog_new (GTK_WINDOW(widget),
						    GTK_DIALOG_DESTROY_WITH_PARENT,
						    GTK_MESSAGE_INFO,
						    GTK_BUTTONS_CLOSE,
						    "%s",
						    _("Certificate exported successfully")));
	gtk_dialog_run (GTK_DIALOG(dialog));

	gtk_widget_destroy (GTK_WIDGET(dialog));


}

almanah_search_dialog_new (void)
{
	GtkBuilder *builder;
	AlmanahSearchDialog *search_dialog;
	AlmanahSearchDialogPrivate *priv;
	GError *error = NULL;
	const gchar *interface_filename = almanah_get_interface_filename ();
	const gchar *object_names[] = {
		"almanah_search_dialog",
		"almanah_sd_search_button_image",
		"almanah_sd_cancel_button_image",
		"almanah_sd_results_store",
		"almanah_ui_manager",
		NULL
	};

	builder = gtk_builder_new ();

	if (gtk_builder_add_objects_from_file (builder, interface_filename, (gchar**) object_names, &error) == FALSE) {

		GtkWidget *dialog = gtk_message_dialog_new (NULL,
				GTK_DIALOG_MODAL,
				GTK_MESSAGE_ERROR,
				GTK_BUTTONS_OK,
				_("UI file \"%s\" could not be loaded"), interface_filename);
		gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "%s", error->message);
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);

		g_error_free (error);
		g_object_unref (builder);

		return NULL;
	}

	gtk_builder_set_translation_domain (builder, GETTEXT_PACKAGE);
	search_dialog = ALMANAH_SEARCH_DIALOG (gtk_builder_get_object (builder, "almanah_search_dialog"));
	gtk_builder_connect_signals (builder, search_dialog);

	if (search_dialog == NULL) {
		g_object_unref (builder);
		return NULL;
	}

	priv = ALMANAH_SEARCH_DIALOG (search_dialog)->priv;

	priv->sd_cancellable = NULL;


	priv->sd_search_entry = GTK_ENTRY (gtk_builder_get_object (builder, "almanah_sd_search_entry"));
	priv->sd_results_store = GTK_LIST_STORE (gtk_builder_get_object (builder, "almanah_sd_results_store"));
	priv->sd_results_selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (gtk_builder_get_object (builder, "almanah_sd_results_tree_view")));
	priv->sd_results_alignment = GTK_WIDGET (gtk_builder_get_object (builder, "almanah_sd_results_alignment"));
	priv->sd_search_spinner = GTK_SPINNER (gtk_builder_get_object (builder, "almanah_sd_search_spinner"));
	priv->sd_results_label = GTK_LABEL (gtk_builder_get_object (builder, "almanah_sd_results_label"));
	priv->sd_search_button = GTK_WIDGET (gtk_builder_get_object (builder, "almanah_sd_search_button"));
	priv->sd_cancel_button = GTK_WIDGET (gtk_builder_get_object (builder, "almanah_sd_cancel_button"));

	g_signal_connect (priv->sd_results_selection, "changed", G_CALLBACK (sd_results_selection_changed_cb),
			  gtk_builder_get_object (builder, "almanah_sd_view_button"));

	gtk_widget_grab_default (priv->sd_search_button);

	g_object_unref (builder);

	return search_dialog;
}

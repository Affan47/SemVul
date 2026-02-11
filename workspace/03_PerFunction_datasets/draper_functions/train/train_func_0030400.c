gsd_message_dialog (GnomeScanDialog *dialog,
					GtkMessageType mtype,
					GtkButtonsType btype,
					const gchar* primary,
					const gchar* secondary)
{
	GtkWidget* message_dialog;
	GtkWindow* parent = NULL;

	g_object_get (dialog, "transient-for", &parent, NULL);
	if (!(parent && GTK_WIDGET_VISIBLE (GTK_WIDGET (parent))) && GTK_WIDGET_VISIBLE (GTK_WIDGET (dialog))) {
		parent = GTK_WINDOW (dialog);
	}
	else {
		parent = NULL;
	}

	message_dialog = gtk_message_dialog_new (parent,
											 GTK_DIALOG_MODAL
											 | GTK_DIALOG_DESTROY_WITH_PARENT,
											 mtype, btype, "%s", g_strdup (primary));
	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (message_dialog),
											  "%s", g_strdup (secondary));

	gtk_dialog_run (GTK_DIALOG (message_dialog));
	gtk_widget_destroy (message_dialog);
}

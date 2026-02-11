brasero_data_disc_deep_directory_cb (BraseroTrackDataCfg *project,
				     const gchar *name,
				     BraseroDataDisc *self)
{
	gint answer;
	gchar *string;
	GtkWidget *dialog;
	BraseroDataDiscPrivate *priv;

	priv = BRASERO_DATA_DISC_PRIVATE (self);

	if (priv->accept_2G_files)
		return TRUE;

	if (priv->reject_2G_files)
		return FALSE;

	string = g_strdup_printf (_("Do you really want to add \"%s\" to the selection?"), name);
	dialog = brasero_app_dialog (brasero_app_get_default (),
				     string,
				     GTK_BUTTONS_NONE,
				     GTK_MESSAGE_WARNING);
	g_free (string);

	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
						  "%s",
						  _("The children of this directory will have 7 parent directories."
						    "\nBrasero can create an image of such a file hierarchy and burn it but the disc may not be readable on all operating systems."
						    "\nNote: Such a file hierarchy is known to work on Linux."));

	gtk_dialog_add_button (GTK_DIALOG (dialog), _("Ne_ver Add Such File"), GTK_RESPONSE_REJECT);
	gtk_dialog_add_button (GTK_DIALOG (dialog), _("Al_ways Add Such File"), GTK_RESPONSE_ACCEPT);

	gtk_widget_show_all (dialog);
	answer = gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);

	priv->accept_2G_files = (answer == GTK_RESPONSE_ACCEPT);
	priv->reject_2G_files = (answer == GTK_RESPONSE_REJECT);

	return (answer != GTK_RESPONSE_YES && answer != GTK_RESPONSE_ACCEPT);
}

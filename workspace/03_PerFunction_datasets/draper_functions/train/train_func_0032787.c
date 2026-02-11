brasero_data_disc_name_collision_cb (BraseroTrackDataCfg *project,
				     const gchar *name,
				     BraseroDataDisc *self)
{
	gint answer;
	gchar *string;
	GtkWidget *dialog;
	BraseroDataDiscPrivate *priv;

	priv = BRASERO_DATA_DISC_PRIVATE (self);

	if (priv->always_replace)
		return FALSE;

	if (priv->never_replace)
		return TRUE;


	string = g_strdup_printf (_("Do you want to replace \"%s\"?"), name);
	dialog = brasero_app_dialog (brasero_app_get_default (),
				     string,
				     GTK_BUTTONS_NONE,
				     GTK_MESSAGE_WARNING);
	g_free (string);

	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
					 "%s", _("A file with this name already exists in the folder.  Replacing it will overwrite its contents on the disc to be burnt."));


	gtk_dialog_add_button (GTK_DIALOG (dialog), _("Always K_eep"), GTK_RESPONSE_REJECT);


	gtk_dialog_add_button (GTK_DIALOG (dialog), _("_Keep"), GTK_RESPONSE_NO);


	gtk_dialog_add_button (GTK_DIALOG (dialog), _("_Replace"), GTK_RESPONSE_YES);


	gtk_dialog_add_button (GTK_DIALOG (dialog), _("Al_ways Replace"), GTK_RESPONSE_ACCEPT);

	gtk_widget_show_all (dialog);
	answer = gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);

	priv->always_replace = (answer == GTK_RESPONSE_ACCEPT);
	priv->never_replace = (answer == GTK_RESPONSE_REJECT);

	return (answer != GTK_RESPONSE_YES && answer != GTK_RESPONSE_ACCEPT);
}

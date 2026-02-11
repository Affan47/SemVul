brasero_sum_dialog_init (BraseroSumDialog *obj)
{
	GtkWidget *box;
	BraseroMedium *medium;
	BraseroSumDialogPrivate *priv;

	priv = BRASERO_SUM_DIALOG_PRIVATE (obj);

	priv->session = brasero_burn_session_new ();

	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 6);

	priv->md5_check = gtk_check_button_new_with_mnemonic (_("Use an _MD5 file to check the disc"));
	gtk_widget_set_tooltip_text (priv->md5_check, _("Use an external .md5 file that stores the checksum of a disc"));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (priv->md5_check), FALSE);
	g_signal_connect (priv->md5_check,
			  "toggled",
			  G_CALLBACK (brasero_sum_dialog_md5_toggled),
			  obj);

	gtk_box_pack_start (GTK_BOX (box),
			    priv->md5_check,
			    TRUE,
			    TRUE,
			    0);

	priv->md5_chooser = gtk_file_chooser_button_new (_("Open an MD5 file"), GTK_FILE_CHOOSER_ACTION_OPEN);
	gtk_file_chooser_set_local_only (GTK_FILE_CHOOSER (priv->md5_chooser), FALSE);
	gtk_widget_set_sensitive (priv->md5_chooser, FALSE);
	gtk_box_pack_start (GTK_BOX (box),
			    priv->md5_chooser,
			    TRUE,
			    TRUE,
			    0);

	gtk_widget_show_all (box);
	brasero_tool_dialog_pack_options (BRASERO_TOOL_DIALOG (obj),
					  box,
					  NULL);

	brasero_tool_dialog_set_button (BRASERO_TOOL_DIALOG (obj),
					_("_Check"),
					GTK_STOCK_FIND,
					NULL);


	brasero_tool_dialog_set_medium_type_shown (BRASERO_TOOL_DIALOG (obj),
						   BRASERO_MEDIA_TYPE_AUDIO|
						   BRASERO_MEDIA_TYPE_DATA);

	medium = brasero_tool_dialog_get_medium (BRASERO_TOOL_DIALOG (obj));
	if (medium) {
		brasero_tool_dialog_set_valid (BRASERO_TOOL_DIALOG (obj), BRASERO_MEDIUM_VALID (brasero_medium_get_status (medium)));
		g_object_unref (medium);
	}
	else
		brasero_tool_dialog_set_valid (BRASERO_TOOL_DIALOG (obj), FALSE);
}

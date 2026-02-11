response_cb (GtkDialog *dialog,
	     gint       response_id)
{
	GladeNamedIconChooserDialogPrivate *priv;

	priv = GLADE_NAMED_ICON_CHOOSER_DIALOG_GET_PRIVATE (dialog);


	if (!(response_id == GTK_RESPONSE_ACCEPT
	    || response_id == GTK_RESPONSE_OK
	    || response_id == GTK_RESPONSE_YES
	    || response_id == GTK_RESPONSE_APPLY))
		return;

	if (!should_respond (GLADE_NAMED_ICON_CHOOSER_DIALOG (dialog)))
	{
		g_signal_stop_emission_by_name (dialog, "response");
	}
}

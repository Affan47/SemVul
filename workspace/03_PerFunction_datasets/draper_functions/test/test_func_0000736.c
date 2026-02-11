on_read_only_dialog_response (GtkWidget *message_area, gint res, Sourceview *sv)
{
	if (res == GTK_RESPONSE_YES)
	{
		gtk_text_view_set_editable (GTK_TEXT_VIEW (sv->priv->view),
									TRUE);
		sv->priv->read_only = FALSE;
	}
	message_area_destroy (message_area);
}

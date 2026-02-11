on_reload_dialog_response (GtkWidget *message_area, gint res, Sourceview *sv)
{
	if (res == GTK_RESPONSE_YES)
	{
		GFile* file = sourceview_io_get_file (sv->priv->io);

		ianjuta_file_open(IANJUTA_FILE(sv),
						  file, NULL);
		g_object_unref (file);

	}
	else
	{

		gtk_text_buffer_set_modified(GTK_TEXT_BUFFER(sv->priv->document), TRUE);
	}
	message_area_destroy (message_area);
}

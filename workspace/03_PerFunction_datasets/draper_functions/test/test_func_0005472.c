gth_image_viewer_page_real_save_as (GthViewerPage *base,
				    FileSavedFunc  func,
				    gpointer       user_data)
{
	GthImageViewerPage *self;
	GtkWidget          *file_sel;
	char               *uri;
	SaveAsData         *data;

	self = GTH_IMAGE_VIEWER_PAGE (base);
	file_sel = gth_file_chooser_dialog_new (_("Save Image"),
						GTK_WINDOW (self->priv->browser),
						"image-saver");

	uri = g_file_get_uri (self->priv->file_data->file);
	gtk_file_chooser_set_uri (GTK_FILE_CHOOSER (file_sel), uri);

	data = g_new0 (SaveAsData, 1);
	data->self = self;
	data->func = func;
	data->file_data = gth_file_data_dup (self->priv->file_data);
	data->user_data = user_data;
	data->file_sel = file_sel;

	g_signal_connect (GTK_DIALOG (file_sel),
			  "response",
			  G_CALLBACK (save_as_response_cb),
			  data);
	g_signal_connect (G_OBJECT (file_sel),
			  "destroy",
			  G_CALLBACK (save_as_destroy_cb),
			  data);

	gtk_window_set_transient_for (GTK_WINDOW (file_sel), GTK_WINDOW (self->priv->browser));
	gtk_window_set_modal (GTK_WINDOW (file_sel), TRUE);
	gtk_widget_show (file_sel);

	g_free (uri);
}

create_album_ready_cb (GObject      *source_object,
		       GAsyncResult *result,
		       gpointer      user_data)
{
	DialogData       *data = user_data;
	PicasaWebService *picasaweb = PICASA_WEB_SERVICE (source_object);
	PicasaWebAlbum   *album;
	GError           *error = NULL;

	album = picasa_web_service_create_album_finish (picasaweb, result, &error);
	if (error != NULL) {
		gth_task_dialog (GTH_TASK (data->service), TRUE, NULL);
		_gtk_error_dialog_from_gerror_show (GTK_WINDOW (data->browser), _("Could not create the album"), error);
		g_clear_error (&error);
		return;
	}

	data->albums = g_list_append (data->albums, album);
	update_album_list (data);
}

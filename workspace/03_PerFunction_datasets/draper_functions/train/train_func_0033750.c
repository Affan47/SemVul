post_photos_ready_cb (GObject      *source_object,
		      GAsyncResult *result,
		      gpointer      user_data)
{
	DialogData *data = user_data;
	GError     *error = NULL;

	data->photos_ids = flickr_service_post_photos_finish (FLICKR_SERVICE (source_object), result, &error);
	if (error != NULL) {
		_gtk_error_dialog_from_gerror_show (GTK_WINDOW (data->browser), _("Could not upload the files"), error);
		g_clear_error (&error);
		gtk_dialog_response (GTK_DIALOG (data->dialog), GTK_RESPONSE_DELETE_EVENT);
		return;
	}

	if (data->photoset == NULL) {
		export_completed_with_success (data);
		return;
	}


	if (data->photoset->id == NULL) {
		char *first_id;

		first_id = data->photos_ids->data;
		flickr_photoset_set_primary (data->photoset, first_id);
		flickr_service_create_photoset (data->service,
						data->photoset,
						data->cancellable,
						create_photoset_ready_cb,
						data);
	}
	else
		add_photos_to_photoset (data);
}

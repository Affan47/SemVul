list_photos_ready_cb (GObject      *source_object,
		      GAsyncResult *result,
		      gpointer      user_data)
{
	DialogData *data = user_data;
	GError     *error = NULL;
	GList      *list;
	GList      *scan;

	gth_task_dialog (GTH_TASK (data->service), TRUE, NULL);

	_g_object_list_unref (data->photos);
	data->photos = facebook_service_list_photos_finish (data->service, result, &error);
	if (error != NULL) {
		if (data->service != NULL)
			gth_task_dialog (GTH_TASK (data->service), TRUE, NULL);
		_gtk_error_dialog_from_gerror_show (GTK_WINDOW (data->browser), _("Could not get the photo list"), error);
		g_clear_error (&error);
		gtk_widget_destroy (data->dialog);
		return;
	}

	list = NULL;
	for (scan = data->photos; scan; scan = scan->next) {
		FacebookPhoto *photo = scan->data;
		GthFileData   *file_data;

		file_data = gth_file_data_new_for_uri (facebook_photo_get_original_url (photo), "image/jpeg");
		g_file_info_set_file_type (file_data->info, G_FILE_TYPE_REGULAR);
		g_file_info_set_size (file_data->info, FAKE_SIZE);
		g_file_info_set_attribute_object (file_data->info, "facebook::object", G_OBJECT (photo));

		list = g_list_prepend (list, file_data);
	}
	gth_file_list_set_files (GTH_FILE_LIST (data->file_list), list);
	update_selection_status (data);
	gtk_widget_set_sensitive (GET_WIDGET ("download_button"), list != NULL);

	_g_object_list_unref (list);
}

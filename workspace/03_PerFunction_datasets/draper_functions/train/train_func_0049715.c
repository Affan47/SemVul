tear_down_upload (UploadData *data, gconstpointer service)
{
	gdata_test_mock_server_start_trace (mock_server, "teardown-upload");


	if (data->updated_photo != NULL) {
		gdata_service_delete_entry (GDATA_SERVICE (service), gdata_picasaweb_service_get_primary_authorization_domain (),
		                            GDATA_ENTRY (data->updated_photo), NULL, NULL);
		g_object_unref (data->updated_photo);
	}

	g_object_unref (data->photo);
	g_object_unref (data->photo_file);
	g_free (data->slug);
	g_free (data->content_type);
	g_object_unref (data->file_stream);
	g_object_unref (data->service);

	gdata_mock_server_end_trace (mock_server);
}

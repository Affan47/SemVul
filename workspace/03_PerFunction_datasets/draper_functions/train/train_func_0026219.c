test_delete_folder (TempFolderData *data, gconstpointer service)
{
	gboolean success;
	GDataEntry *updated_folder;
	GError *error = NULL;

	gdata_test_mock_server_start_trace (mock_server, "delete-folder");

	g_assert (gdata_documents_entry_is_deleted (GDATA_DOCUMENTS_ENTRY (data->folder)) == FALSE);


	success = gdata_service_delete_entry (GDATA_SERVICE (service), gdata_documents_service_get_primary_authorization_domain (),
	                                      GDATA_ENTRY (data->folder), NULL, &error);
	g_assert_no_error (error);
	g_assert (success == TRUE);
	g_clear_error (&error);


	updated_folder = gdata_service_query_single_entry (GDATA_SERVICE (service), gdata_documents_service_get_primary_authorization_domain (),
	                                                   gdata_entry_get_id (GDATA_ENTRY (data->folder)), NULL,
	                                                   GDATA_TYPE_DOCUMENTS_FOLDER, NULL, &error);
	g_assert_no_error (error);
	g_assert (GDATA_IS_DOCUMENTS_FOLDER (updated_folder));
	g_clear_error (&error);

	g_assert (gdata_documents_entry_is_deleted (GDATA_DOCUMENTS_ENTRY (updated_folder)) == TRUE);

	g_object_unref (updated_folder);
	g_object_unref (data->folder);
	data->folder = NULL;

	gdata_mock_server_end_trace (mock_server);
}

test_photo_add (TempContactData *data, gconstpointer service)
{
	guint8 *photo_data;
	gsize length;
	gboolean retval;
	GError *error = NULL;

	gdata_test_mock_server_start_trace (mock_server, "photo-add");


	g_assert (g_file_get_contents (TEST_FILE_DIR "photo.jpg", (gchar**) &photo_data, &length, NULL) == TRUE);


	retval = gdata_contacts_contact_set_photo (data->contact, GDATA_CONTACTS_SERVICE (service), photo_data, length, "image/jpeg", NULL, &error);
	g_assert_no_error (error);
	g_assert (retval == TRUE);

	g_clear_error (&error);
	g_free (photo_data);

	gdata_mock_server_end_trace (mock_server);
}

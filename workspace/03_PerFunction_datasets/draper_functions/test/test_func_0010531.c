create_album_ready_cb (SoupSession *session,
		       SoupMessage *msg,
		       gpointer     user_data)
{
	CreateAlbumData    *create_album_data = user_data;
	PhotobucketService *self = create_album_data->service;
	GSimpleAsyncResult *result;
	DomDocument        *doc = NULL;
	GError             *error = NULL;

	result = _web_service_get_result (WEB_SERVICE (self));

	if (photobucket_utils_parse_response (msg, &doc, &error)) {
		g_simple_async_result_set_op_res_gpointer (result, g_object_ref (create_album_data->album), g_object_unref);
		g_object_unref (doc);
	}
	else
		g_simple_async_result_set_from_error (result, error);

	g_simple_async_result_complete_in_idle (result);

	create_album_data_free (create_album_data);
}

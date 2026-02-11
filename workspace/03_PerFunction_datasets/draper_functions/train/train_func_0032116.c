test_client_login_authorizer_process_request_insecure_subprocess (ClientLoginAuthorizerData *data, gconstpointer user_data)
{
	SoupMessage *message;


	message = soup_message_new (SOUP_METHOD_GET, "http://example.com/");
	gdata_authorizer_process_request (GDATA_AUTHORIZER (data->authorizer), gdata_youtube_service_get_primary_authorization_domain (),
	                                  message);
	g_object_unref (message);
}

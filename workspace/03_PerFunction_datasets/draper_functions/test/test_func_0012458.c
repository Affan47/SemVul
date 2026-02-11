test_client_login_authorizer_properties_client_id (ClientLoginAuthorizerData *data, gconstpointer user_data)
{
	gchar *client_id;


	g_assert_cmpstr (gdata_client_login_authorizer_get_client_id (data->authorizer), ==, "client-id");

	g_object_get (data->authorizer, "client-id", &client_id, NULL);
	g_assert_cmpstr (client_id, ==, "client-id");
	g_free (client_id);
}

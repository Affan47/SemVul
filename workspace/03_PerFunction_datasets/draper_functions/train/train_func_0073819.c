test_build_with_token_info (void)
{
	gchar *uri = NULL;
	GckUriData uri_data;
	GckUriData *check;

	memset (&uri_data, 0, sizeof (uri_data));
	uri_data.token_info = g_new0 (GckTokenInfo, 1);
	uri_data.token_info->label = g_strdup ("The Label");
	uri_data.token_info->serial_number = g_strdup ("44444");
	uri_data.token_info->manufacturer_id = g_strdup ("Me");
	uri_data.token_info->model = g_strdup ("Deluxe");

	uri = gck_uri_build (&uri_data, GCK_URI_FOR_TOKEN);
	g_assert (uri);

	check = gck_uri_parse (uri, GCK_URI_FOR_TOKEN, NULL);
	g_assert (check);
	g_assert (check->token_info);

	g_assert (_gck_token_info_match (uri_data.token_info, check->token_info));

	gck_token_info_free (uri_data.token_info);
	gck_uri_data_free (check);

	g_assert (g_str_has_prefix (uri, "pkcs11:"));
	g_assert (strstr (uri, "token=The%20Label"));
	g_assert (strstr (uri, "serial=44444"));
	g_assert (strstr (uri, "manufacturer=Me"));
	g_assert (strstr (uri, "model=Deluxe"));

	g_free (uri);
}

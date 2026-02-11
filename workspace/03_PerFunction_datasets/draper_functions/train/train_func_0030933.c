test_read_wired_8021x_tls_blob_connection (void)
{
	NMConnection *connection;
	NMSettingWired *s_wired;
	NMSetting8021x *s_8021x;
	GError *error = NULL;
	const char *tmp;
	gboolean success;
	const GByteArray *array;

	connection = nm_keyfile_plugin_connection_from_file (TEST_WIRED_TLS_BLOB_FILE, &error);
	if (connection == NULL) {
		g_assert (error);
		g_warning ("Failed to read %s: %s", TEST_WIRED_TLS_BLOB_FILE, error->message);
		g_assert (connection);
	}

	success = nm_connection_verify (connection, &error);
	if (!success) {
		g_assert (error);
		g_warning ("Failed to verify %s: %s", TEST_WIRED_TLS_BLOB_FILE, error->message);
		g_assert (success);
	}


	s_wired = nm_connection_get_setting_wired (connection);
	g_assert (s_wired != NULL);


	s_8021x = nm_connection_get_setting_802_1x (connection);
	g_assert (s_8021x != NULL);

	g_assert (nm_setting_802_1x_get_num_eap_methods (s_8021x) == 1);
	tmp = nm_setting_802_1x_get_eap_method (s_8021x, 0);
	g_assert (g_strcmp0 (tmp, "tls") == 0);

	tmp = nm_setting_802_1x_get_identity (s_8021x);
	g_assert (g_strcmp0 (tmp, "Bill Smith") == 0);

	tmp = nm_setting_802_1x_get_private_key_password (s_8021x);
	g_assert (g_strcmp0 (tmp, "12345testing") == 0);

	g_assert_cmpint (nm_setting_802_1x_get_ca_cert_scheme (s_8021x), ==, NM_SETTING_802_1X_CK_SCHEME_BLOB);


	tmp = nm_setting_802_1x_get_ca_cert_path (s_8021x);
	g_assert (tmp == NULL);


	array = nm_setting_802_1x_get_ca_cert_blob (s_8021x);
	g_assert (array != NULL);
	g_assert_cmpint (array->len, ==, 568);

	tmp = nm_setting_802_1x_get_client_cert_path (s_8021x);
	g_assert_cmpstr (tmp, ==, "/home/dcbw/Desktop/certinfra/client.pem");

	tmp = nm_setting_802_1x_get_private_key_path (s_8021x);
	g_assert_cmpstr (tmp, ==, "/home/dcbw/Desktop/certinfra/client.pem");

	g_object_unref (connection);
}

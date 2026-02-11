test_write_bt_dun_connection (void)
{
	NMConnection *connection;
	NMSettingConnection *s_con;
	NMSettingBluetooth *s_bt;
	NMSettingIP4Config *s_ip4;
	NMSettingGsm *s_gsm;
	char *uuid;
	GByteArray *bdaddr;
	unsigned char tmpbdaddr[] = { 0xaa, 0xb9, 0xa1, 0x74, 0x55, 0x44 };
	gboolean success;
	NMConnection *reread;
	char *testfile = NULL;
	GError *error = NULL;
	pid_t owner_grp;
	uid_t owner_uid;
	guint64 timestamp = 0x12344433L;

	connection = nm_connection_new ();
	ASSERT (connection != NULL,
	        "connection-write", "failed to allocate new connection");


	s_con = NM_SETTING_CONNECTION (nm_setting_connection_new ());
	ASSERT (s_con != NULL,
	        "connection-write", "failed to allocate new %s setting",
	        NM_SETTING_CONNECTION_SETTING_NAME);
	nm_connection_add_setting (connection, NM_SETTING (s_con));

	uuid = nm_utils_uuid_generate ();
	g_object_set (s_con,
	              NM_SETTING_CONNECTION_ID, "T-Mobile Funkadelic",
	              NM_SETTING_CONNECTION_UUID, uuid,
	              NM_SETTING_CONNECTION_AUTOCONNECT, FALSE,
	              NM_SETTING_CONNECTION_TYPE, NM_SETTING_BLUETOOTH_SETTING_NAME,
	              NM_SETTING_CONNECTION_TIMESTAMP, timestamp,
	              NULL);
	g_free (uuid);


	s_bt = NM_SETTING_BLUETOOTH (nm_setting_bluetooth_new ());
	ASSERT (s_bt != NULL,
			"connection-write", "failed to allocate new %s setting",
			NM_SETTING_BLUETOOTH_SETTING_NAME);
	nm_connection_add_setting (connection, NM_SETTING (s_bt));

	bdaddr = g_byte_array_sized_new (ETH_ALEN);
	g_byte_array_append (bdaddr, &tmpbdaddr[0], sizeof (tmpbdaddr));

	g_object_set (s_bt,
	              NM_SETTING_BLUETOOTH_BDADDR, bdaddr,
	              NM_SETTING_BLUETOOTH_TYPE, NM_SETTING_BLUETOOTH_TYPE_DUN,
	              NULL);

	g_byte_array_free (bdaddr, TRUE);


	s_ip4 = NM_SETTING_IP4_CONFIG (nm_setting_ip4_config_new ());
	ASSERT (s_ip4 != NULL,
			"connection-write", "failed to allocate new %s setting",
			NM_SETTING_IP4_CONFIG_SETTING_NAME);
	nm_connection_add_setting (connection, NM_SETTING (s_ip4));

	g_object_set (s_ip4,
	              NM_SETTING_IP4_CONFIG_METHOD, NM_SETTING_IP4_CONFIG_METHOD_AUTO,
	              NULL);


	s_gsm = NM_SETTING_GSM (nm_setting_gsm_new ());
	ASSERT (s_gsm != NULL,
			"connection-write", "failed to allocate new %s setting",
			NM_SETTING_GSM_SETTING_NAME);
	nm_connection_add_setting (connection, NM_SETTING (s_gsm));

	g_object_set (s_gsm,
	              NM_SETTING_GSM_APN, "internet2.voicestream.com",
	              NM_SETTING_GSM_USERNAME, "george.clinton",
	              NM_SETTING_GSM_PASSWORD, "parliament",
	              NM_SETTING_GSM_NUMBER,  "*99#",
	              NULL);


	owner_uid = geteuid ();
	owner_grp = getegid ();
	success = nm_keyfile_plugin_write_test_connection (connection, TEST_SCRATCH_DIR, owner_uid, owner_grp, &testfile, &error);
	ASSERT (success == TRUE,
			"connection-write", "failed to write keyfile: %s",
			error ? error->message : "(none)");

	ASSERT (testfile != NULL,
			"connection-write", "didn't get keyfile name back after writing connection");


	reread = nm_keyfile_plugin_connection_from_file (testfile, NULL);
	ASSERT (reread != NULL, "connection-write", "failed to re-read test connection");

	ASSERT (nm_connection_compare (connection, reread, NM_SETTING_COMPARE_FLAG_EXACT) == TRUE,
			"connection-write", "written and re-read connection weren't the same");

	g_clear_error (&error);
	unlink (testfile);
	g_free (testfile);

	g_object_unref (reread);
	g_object_unref (connection);
}

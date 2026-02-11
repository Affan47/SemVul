get_settings_auth_cb (NMSettingsConnection *self,
                      DBusGMethodInvocation *context,
                      gulong sender_uid,
                      GError *error,
                      gpointer data)
{
	if (error)
		dbus_g_method_return_error (context, error);
	else {
		GHashTable *settings;
		NMConnection *dupl_con;
		NMSettingConnection *s_con;
		NMSettingWireless *s_wifi;
		guint64 timestamp = 0;
		GSList *bssid_list;

		dupl_con = nm_connection_duplicate (NM_CONNECTION (self));
		g_assert (dupl_con);


		nm_settings_connection_get_timestamp (self, &timestamp);
		if (timestamp) {
			s_con = nm_connection_get_setting_connection (NM_CONNECTION (dupl_con));
			g_assert (s_con);
			g_object_set (s_con, NM_SETTING_CONNECTION_TIMESTAMP, timestamp, NULL);
		}


		bssid_list = nm_settings_connection_get_seen_bssids (self);
		s_wifi = nm_connection_get_setting_wireless (NM_CONNECTION (dupl_con));
		if (bssid_list && s_wifi) {
			g_object_set (s_wifi, NM_SETTING_WIRELESS_SEEN_BSSIDS, bssid_list, NULL);
			nm_utils_slist_free (bssid_list, g_free);
		}


		settings = nm_connection_to_hash (NM_CONNECTION (dupl_con), NM_SETTING_HASH_FLAG_NO_SECRETS);
		g_assert (settings);
		dbus_g_method_return (context, settings);
		g_hash_table_destroy (settings);
		g_object_unref (dupl_con);
	}
}

get_best_auto_connection (NMModem *_self,
                          GSList *connections,
                          char **specific_object)
{
	NMModemBroadband *self = NM_MODEM_BROADBAND (_self);
	MMModemCapability modem_caps;
	GSList *iter;

	modem_caps = mm_modem_get_current_capabilities (self->priv->modem_iface);

	for (iter = connections; iter; iter = g_slist_next (iter)) {
		NMConnection *connection = NM_CONNECTION (iter->data);
		NMSettingConnection *s_con;

		s_con = nm_connection_get_setting_connection (connection);
		g_assert (s_con);

		if (!nm_setting_connection_get_autoconnect (s_con))
			continue;


		if (   g_str_equal (nm_setting_connection_get_connection_type (s_con),
		                    NM_SETTING_GSM_SETTING_NAME)
		    && MODEM_CAPS_3GPP (modem_caps))
			return connection;


		if (   g_str_equal (nm_setting_connection_get_connection_type (s_con),
		                    NM_SETTING_CDMA_SETTING_NAME)
		    && MODEM_CAPS_3GPP2 (modem_caps))
			return connection;


	}

	return NULL;
}

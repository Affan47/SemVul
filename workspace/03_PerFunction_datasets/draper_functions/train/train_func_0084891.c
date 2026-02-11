connection_compatible (NMDevice *device, NMConnection *connection, GError **error)
{
	NMSettingConnection *s_con;
	NMSettingGsm *s_gsm;
	NMSettingCdma *s_cdma;
	const char *ctype;
	NMDeviceModemCapabilities current_caps;

	g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

	s_con = nm_connection_get_setting_connection (connection);
	g_assert (s_con);

	ctype = nm_setting_connection_get_connection_type (s_con);
	if (   strcmp (ctype, NM_SETTING_GSM_SETTING_NAME) != 0
	    && strcmp (ctype, NM_SETTING_CDMA_SETTING_NAME) != 0) {
		g_set_error (error, NM_DEVICE_MODEM_ERROR, NM_DEVICE_MODEM_ERROR_NOT_MODEM_CONNECTION,
		             "The connection was not a modem connection.");
		return FALSE;
	}

	s_gsm = nm_connection_get_setting_gsm (connection);
	s_cdma = nm_connection_get_setting_cdma (connection);
	if (!s_cdma && !s_gsm) {
		g_set_error (error, NM_DEVICE_MODEM_ERROR, NM_DEVICE_MODEM_ERROR_INVALID_MODEM_CONNECTION,
		             "The connection was not a valid modem connection.");
		return FALSE;
	}

	current_caps = nm_device_modem_get_current_capabilities (NM_DEVICE_MODEM (device));
	if (   !(s_gsm && (current_caps & NM_DEVICE_MODEM_CAPABILITY_GSM_UMTS))
	    && !(s_cdma && (current_caps & NM_DEVICE_MODEM_CAPABILITY_CDMA_EVDO))) {
		g_set_error (error, NM_DEVICE_MODEM_ERROR, NM_DEVICE_MODEM_ERROR_MISSING_DEVICE_CAPS,
		             "The device missed capabilities required by the GSM/CDMA connection.");
		return FALSE;
	}

	return TRUE;
}

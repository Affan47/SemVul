nm_device_wifi_get_ipw_rfkill_state (NMDeviceWifi *self)
{
	NMDeviceWifiPrivate *priv = NM_DEVICE_WIFI_GET_PRIVATE (self);
	char *contents = NULL;
	RfKillState state = RFKILL_UNBLOCKED;
	const char *str_state = NULL;

	if (   priv->ipw_rfkill_path
	    && g_file_get_contents (priv->ipw_rfkill_path, &contents, NULL, NULL)) {
		contents = g_strstrip (contents);


		switch (contents[0]) {
		case '1':
			state = RFKILL_SOFT_BLOCKED;
			str_state = "soft-blocked";
			break;
		case '2':
		case '3':
			state = RFKILL_HARD_BLOCKED;
			str_state = "hard-blocked";
			break;
		case '0':
			str_state = "unblocked";
		default:
			break;
		}
		g_free (contents);

		nm_log_dbg (LOGD_RFKILL, "(%s): ipw rfkill state '%s'",
		            nm_device_get_iface (NM_DEVICE (self)),
		            str_state ? str_state : "(unknown)");
	}

	return state;
}

check_connection_compatible (NMDevice *device,
                             NMConnection *connection,
                             GError **error)
{
	NMDeviceWifi *self = NM_DEVICE_WIFI (device);
	NMDeviceWifiPrivate *priv = NM_DEVICE_WIFI_GET_PRIVATE (self);
	NMSettingConnection *s_con;
	NMSettingWireless *s_wireless;
	const GByteArray *mac;
	const GSList *mac_blacklist, *mac_blacklist_iter;
	const char *mode;

	s_con = nm_connection_get_setting_connection (connection);
	g_assert (s_con);

	if (strcmp (nm_setting_connection_get_connection_type (s_con), NM_SETTING_WIRELESS_SETTING_NAME)) {
		g_set_error (error,
		             NM_WIFI_ERROR, NM_WIFI_ERROR_CONNECTION_NOT_WIRELESS,
		             "The connection was not a WiFi connection.");
		return FALSE;
	}

	s_wireless = nm_connection_get_setting_wireless (connection);
	if (!s_wireless) {
		g_set_error (error,
		             NM_WIFI_ERROR, NM_WIFI_ERROR_CONNECTION_INVALID,
		             "The connection was not a valid WiFi connection.");
		return FALSE;
	}


	mac = nm_setting_wireless_get_mac_address (s_wireless);
	if (mac && memcmp (mac->data, &priv->perm_hw_addr, ETH_ALEN)) {
		g_set_error (error,
		             NM_WIFI_ERROR, NM_WIFI_ERROR_CONNECTION_INCOMPATIBLE,
		             "The connection's MAC address did not match this device.");
		return FALSE;
	}


	mac_blacklist = nm_setting_wireless_get_mac_address_blacklist (s_wireless);
	for (mac_blacklist_iter = mac_blacklist; mac_blacklist_iter;
	     mac_blacklist_iter = g_slist_next (mac_blacklist_iter)) {
		struct ether_addr addr;

		if (!ether_aton_r (mac_blacklist_iter->data, &addr)) {
			g_warn_if_reached ();
			continue;
		}
		if (memcmp (&addr, &priv->perm_hw_addr, ETH_ALEN) == 0) {
			g_set_error (error,
			             NM_WIFI_ERROR, NM_WIFI_ERROR_CONNECTION_INCOMPATIBLE,
			             "The connection's MAC address (%s) is blacklisted in %s.",
			             (char *) mac_blacklist_iter->data, NM_SETTING_WIRELESS_MAC_ADDRESS_BLACKLIST);
			return FALSE;
		}
	}


	mode = nm_setting_wireless_get_mode (s_wireless);
	if (g_strcmp0 (mode, NM_SETTING_WIRELESS_MODE_ADHOC) == 0) {
		if (!(priv->capabilities & NM_WIFI_DEVICE_CAP_ADHOC)) {
			g_set_error_literal (error,
			                     NM_WIFI_ERROR,
			                     NM_WIFI_ERROR_ADHOC_MODE_UNSUPPORTED,
			                     "Ad-Hoc mode is not supported by this device.");
			return FALSE;
		}
	} else if (g_strcmp0 (mode, NM_SETTING_WIRELESS_MODE_AP) == 0) {
		if (!(priv->capabilities & NM_WIFI_DEVICE_CAP_AP)) {
			g_set_error_literal (error,
			                     NM_WIFI_ERROR,
			                     NM_WIFI_ERROR_AP_MODE_UNSUPPORTED,
			                     "Access Point (AP) mode is not supported by this device.");
			return FALSE;
		}

		if (priv->supplicant.iface) {
			switch (nm_supplicant_interface_get_ap_support (priv->supplicant.iface)) {
			case AP_SUPPORT_NO:
				g_set_error_literal (error,
				                     NM_WIFI_ERROR,
				                     NM_WIFI_ERROR_AP_MODE_UNSUPPORTED,
				                     "Access Point (AP) mode is not supported by the supplicant.");
				return FALSE;
			case AP_SUPPORT_YES:
			case AP_SUPPORT_UNKNOWN:
			default:
				break;
			}
		}
	}


	return TRUE;
}

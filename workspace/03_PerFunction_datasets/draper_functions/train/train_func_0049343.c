wext_get_caps (WifiDataWext *wext, struct iw_range *range)
{
	guint32 caps = NM_WIFI_DEVICE_CAP_NONE;

	g_return_val_if_fail (wext != NULL, NM_WIFI_DEVICE_CAP_NONE);
	g_return_val_if_fail (range != NULL, NM_WIFI_DEVICE_CAP_NONE);


	caps |= NM_WIFI_DEVICE_CAP_CIPHER_WEP40 | NM_WIFI_DEVICE_CAP_CIPHER_WEP104;

	if (range->enc_capa & IW_ENC_CAPA_CIPHER_TKIP)
		caps |= NM_WIFI_DEVICE_CAP_CIPHER_TKIP;

	if (range->enc_capa & IW_ENC_CAPA_CIPHER_CCMP)
		caps |= NM_WIFI_DEVICE_CAP_CIPHER_CCMP;

	if (range->enc_capa & IW_ENC_CAPA_WPA)
		caps |= NM_WIFI_DEVICE_CAP_WPA;

	if (range->enc_capa & IW_ENC_CAPA_WPA2)
		caps |= NM_WIFI_DEVICE_CAP_RSN;


	if (    (caps & (NM_WIFI_DEVICE_CAP_CIPHER_TKIP | NM_WIFI_DEVICE_CAP_CIPHER_CCMP))
	    && !(caps & (NM_WIFI_DEVICE_CAP_WPA | NM_WIFI_DEVICE_CAP_RSN))) {
		nm_log_warn (LOGD_WIFI, "%s: device supports WPA ciphers but not WPA protocol; "
		             "WPA unavailable.", wext->parent.iface);
		caps &= ~WPA_CAPS;
	}


	if (    (caps & (NM_WIFI_DEVICE_CAP_WPA | NM_WIFI_DEVICE_CAP_RSN))
	    && !(caps & (NM_WIFI_DEVICE_CAP_CIPHER_TKIP | NM_WIFI_DEVICE_CAP_CIPHER_CCMP))) {
		nm_log_warn (LOGD_WIFI, "%s: device supports WPA protocol but not WPA ciphers; "
		             "WPA unavailable.", wext->parent.iface);
		caps &= ~WPA_CAPS;
	}


	caps |= NM_WIFI_DEVICE_CAP_ADHOC;

	return caps;
}

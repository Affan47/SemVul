act_stage2_config (NMDevice *dev, NMDeviceStateReason *reason)
{
	NMDeviceWifi *self = NM_DEVICE_WIFI (dev);
	NMDeviceWifiPrivate *priv = NM_DEVICE_WIFI_GET_PRIVATE (self);
	NMActStageReturn ret = NM_ACT_STAGE_RETURN_FAILURE;
	const char *iface = nm_device_get_iface (dev);
	NMSupplicantConfig *config = NULL;
	gulong id = 0;
	NMActRequest *req;
	NMAccessPoint *ap;
	NMConnection *connection;
	const char *setting_name;
	NMSettingWireless *s_wireless;

	g_return_val_if_fail (reason != NULL, NM_ACT_STAGE_RETURN_FAILURE);

	remove_supplicant_timeouts (self);

	req = nm_device_get_act_request (dev);
	g_assert (req);

	ap = nm_device_wifi_get_activation_ap (self);
	g_assert (ap);

	connection = nm_act_request_get_connection (req);
	g_assert (connection);

	s_wireless = nm_connection_get_setting_wireless (connection);
	g_assert (s_wireless);


	setting_name = nm_connection_need_secrets (connection, NULL);
	if (setting_name) {
		nm_log_info (LOGD_DEVICE | LOGD_WIFI,
		             "Activation (%s/wireless): access point '%s' has security,"
		             " but secrets are required.",
		             iface, nm_connection_get_id (connection));

		ret = handle_auth_or_fail (self, req, FALSE);
		if (ret == NM_ACT_STAGE_RETURN_FAILURE)
			*reason = NM_DEVICE_STATE_REASON_NO_SECRETS;
		goto out;
	}


	if (nm_setting_wireless_get_security (s_wireless)) {
		nm_log_info (LOGD_DEVICE | LOGD_WIFI,
		             "Activation (%s/wireless): connection '%s' has security"
		             ", and secrets exist.  No new secrets needed.",
		             iface, nm_connection_get_id (connection));
	} else {
		nm_log_info (LOGD_DEVICE | LOGD_WIFI,
		             "Activation (%s/wireless): connection '%s' requires no "
		             "security.  No secrets needed.",
		             iface, nm_connection_get_id (connection));
	}

	priv->ssid_found = FALSE;


	if ((nm_ap_get_mode (ap) == NM_802_11_MODE_ADHOC) || nm_ap_is_hotspot (ap))
		ensure_hotspot_frequency (self, s_wireless, ap);


	config = build_supplicant_config (self, connection, ap);
	if (config == NULL) {
		nm_log_err (LOGD_DEVICE | LOGD_WIFI,
		             "Activation (%s/wireless): couldn't build wireless configuration.",
		             iface);
		*reason = NM_DEVICE_STATE_REASON_SUPPLICANT_CONFIG_FAILED;
		goto out;
	}


	id = g_signal_connect (priv->supplicant.iface,
	                       NM_SUPPLICANT_INTERFACE_CONNECTION_ERROR,
	                       G_CALLBACK (supplicant_iface_connection_error_cb),
	                       self);
	priv->supplicant.iface_error_id = id;

	if (!nm_supplicant_interface_set_config (priv->supplicant.iface, config)) {
		nm_log_err (LOGD_DEVICE | LOGD_WIFI,
		            "Activation (%s/wireless): couldn't send wireless "
		            "configuration to the supplicant.", iface);
		*reason = NM_DEVICE_STATE_REASON_SUPPLICANT_CONFIG_FAILED;
		goto out;
	}

	if (!start_supplicant_connection_timeout (self)) {
		*reason = NM_DEVICE_STATE_REASON_SUPPLICANT_CONFIG_FAILED;
		goto out;
	}


	ret = NM_ACT_STAGE_RETURN_POSTPONE;

out:
	if (ret == NM_ACT_STAGE_RETURN_FAILURE)
		cleanup_association_attempt (self, TRUE);

	if (config) {


		g_object_unref (config);
	}
	return ret;
}

link_timeout_cb (gpointer user_data)
{
	NMDeviceEthernet *self = NM_DEVICE_ETHERNET (user_data);
	NMDeviceEthernetPrivate *priv = NM_DEVICE_ETHERNET_GET_PRIVATE (self);
	NMDevice *dev = NM_DEVICE (self);
	NMActRequest *req;
	NMConnection *connection;
	const char *setting_name;

	priv->supplicant_timeout_id = 0;

	req = nm_device_get_act_request (dev);

	if (nm_device_get_state (dev) == NM_DEVICE_STATE_ACTIVATED) {
		nm_device_state_changed (dev,
		                         NM_DEVICE_STATE_FAILED,
		                         NM_DEVICE_STATE_REASON_SUPPLICANT_TIMEOUT);
		return FALSE;
	}


	if (nm_device_get_state (dev) != NM_DEVICE_STATE_CONFIG)
		goto time_out;

	connection = nm_act_request_get_connection (req);
	nm_connection_clear_secrets (connection);
	setting_name = nm_connection_need_secrets (connection, NULL);
	if (!setting_name)
		goto time_out;

	nm_log_info (LOGD_DEVICE | LOGD_ETHER,
	             "Activation (%s/wired): disconnected during authentication,"
	             " asking for new key.",
	             nm_device_get_iface (dev));
	supplicant_interface_release (self);

	nm_device_state_changed (dev, NM_DEVICE_STATE_NEED_AUTH, NM_DEVICE_STATE_REASON_SUPPLICANT_DISCONNECT);
	nm_act_request_get_secrets (req,
	                            setting_name,
	                            NM_SETTINGS_GET_SECRETS_FLAG_REQUEST_NEW,
	                            NULL,
	                            wired_secrets_cb,
	                            self);

	return FALSE;

time_out:
	nm_log_warn (LOGD_DEVICE | LOGD_ETHER,
	             "(%s): link timed out.", nm_device_get_iface (dev));
	nm_device_state_changed (dev, NM_DEVICE_STATE_FAILED, NM_DEVICE_STATE_REASON_SUPPLICANT_DISCONNECT);

	return FALSE;
}

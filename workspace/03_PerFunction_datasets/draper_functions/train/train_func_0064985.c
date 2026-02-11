nm_8021x_stage2_config (NMDeviceEthernet *self, NMDeviceStateReason *reason)
{
	NMConnection *connection;
	NMSetting8021x *security;
	const char *setting_name;
	const char *iface;
	NMActStageReturn ret = NM_ACT_STAGE_RETURN_FAILURE;

	connection = nm_device_get_connection (NM_DEVICE (self));
	g_assert (connection);
	security = nm_connection_get_setting_802_1x (connection);
	if (!security) {
		nm_log_err (LOGD_DEVICE, "Invalid or missing 802.1X security");
		*reason = NM_DEVICE_STATE_REASON_CONFIG_FAILED;
		return ret;
	}

	iface = nm_device_get_iface (NM_DEVICE (self));


	setting_name = nm_connection_need_secrets (connection, NULL);
	if (setting_name) {
		NMActRequest *req = nm_device_get_act_request (NM_DEVICE (self));

		nm_log_info (LOGD_DEVICE | LOGD_ETHER,
		             "Activation (%s/wired): connection '%s' has security, but secrets are required.",
				     iface, nm_connection_get_id (connection));

		ret = handle_auth_or_fail (self, req, FALSE);
		if (ret != NM_ACT_STAGE_RETURN_POSTPONE)
			*reason = NM_DEVICE_STATE_REASON_NO_SECRETS;
	} else {
		nm_log_info (LOGD_DEVICE | LOGD_ETHER,
		             "Activation (%s/wired): connection '%s' requires no security. No secrets needed.",
				     iface, nm_connection_get_id (connection));

		if (supplicant_interface_init (self))
			ret = NM_ACT_STAGE_RETURN_POSTPONE;
		else
			*reason = NM_DEVICE_STATE_REASON_CONFIG_FAILED;
	}

	return ret;
}

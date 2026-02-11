nm_device_activate_ip4_config_commit (gpointer user_data)
{
	NMDevice *self = NM_DEVICE (user_data);
	NMDevicePrivate *priv = NM_DEVICE_GET_PRIVATE (self);
	NMActRequest *req;
	NMIP4Config *config = NULL;
	const char *iface, *method = NULL;
	NMConnection *connection;
	NMSettingIP4Config *s_ip4;
	NMDeviceStateReason reason = NM_DEVICE_STATE_REASON_NONE;
	gboolean assumed;
	int ifindex;


	activation_source_clear (self, FALSE, AF_INET);

	iface = nm_device_get_iface (self);
	nm_log_info (LOGD_DEVICE, "Activation (%s) Stage 5 of 5 (IPv4 Commit) started...",
	             iface);

	req = nm_device_get_act_request (self);
	g_assert (req);
	connection = nm_act_request_get_connection (req);
	g_assert (connection);

	config = g_object_get_data (G_OBJECT (req), PENDING_IP4_CONFIG);
	g_assert (config);


	ifindex = nm_device_get_ip_ifindex (self);
	if ((ifindex > 0) && (nm_system_iface_is_up (ifindex) == FALSE))
		nm_system_iface_set_up (ifindex, TRUE, NULL);


	if (NM_DEVICE_GET_CLASS (self)->ip4_config_pre_commit)
		NM_DEVICE_GET_CLASS (self)->ip4_config_pre_commit (self, config);


	nm_utils_merge_ip4_config (config, nm_connection_get_setting_ip4_config (connection));

	assumed = nm_active_connection_get_assumed (NM_ACTIVE_CONNECTION (priv->act_request));
	if (!nm_device_set_ip4_config (self, config, assumed, &reason)) {
		nm_log_info (LOGD_DEVICE | LOGD_IP4,
			         "Activation (%s) Stage 5 of 5 (IPv4 Commit) failed",
					 iface);
		nm_device_state_changed (self, NM_DEVICE_STATE_FAILED, reason);
		goto out;
	}


	s_ip4 = nm_connection_get_setting_ip4_config (connection);
	if (s_ip4)
		method = nm_setting_ip4_config_get_method (s_ip4);

	if (g_strcmp0 (method, NM_SETTING_IP4_CONFIG_METHOD_SHARED) == 0) {
		if (!start_sharing (self, config)) {
			nm_log_warn (LOGD_SHARING, "Activation (%s) Stage 5 of 5 (IPv4 Commit) start sharing failed.", iface);
			nm_device_state_changed (self, NM_DEVICE_STATE_FAILED, NM_DEVICE_STATE_REASON_SHARED_START_FAILED);
			goto out;
		}
	}


	priv->ip4_state = IP_DONE;
	if (nm_device_get_state (self) == NM_DEVICE_STATE_IP_CONFIG)
		nm_device_state_changed (self, NM_DEVICE_STATE_SECONDARIES, NM_DEVICE_STATE_REASON_NONE);

out:
	nm_log_info (LOGD_DEVICE, "Activation (%s) Stage 5 of 5 (IPv4 Commit) complete.",
	             iface);


	g_object_set_data (G_OBJECT (req), PENDING_IP4_CONFIG, NULL);

	return FALSE;
}

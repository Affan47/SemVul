nm_vpn_manager_activate_connection (NMVPNManager *manager,
                                    NMConnection *connection,
                                    NMDevice *device,
                                    const char *specific_object,
                                    gboolean user_requested,
                                    gulong user_uid,
                                    GError **error)
{
	NMSettingVPN *vpn_setting;
	NMVPNService *service;
	NMVPNConnection *vpn = NULL;
	const char *service_name;

	g_return_val_if_fail (NM_IS_VPN_MANAGER (manager), NULL);
	g_return_val_if_fail (NM_IS_CONNECTION (connection), NULL);
	g_return_val_if_fail (NM_IS_DEVICE (device), NULL);
	g_return_val_if_fail (error != NULL, NULL);
	g_return_val_if_fail (*error == NULL, NULL);

	if (   nm_device_get_state (device) != NM_DEVICE_STATE_ACTIVATED
	    && nm_device_get_state (device) != NM_DEVICE_STATE_SECONDARIES) {
		g_set_error (error,
		             NM_VPN_MANAGER_ERROR, NM_VPN_MANAGER_ERROR_DEVICE_NOT_ACTIVE,
		             "%s", "The base device for the VPN connection was not active.");
		return NULL;
	}

	vpn_setting = nm_connection_get_setting_vpn (connection);
	if (!vpn_setting) {
		g_set_error (error,
		             NM_VPN_MANAGER_ERROR, NM_VPN_MANAGER_ERROR_CONNECTION_INVALID,
		             "%s", "The connection was not a VPN connection.");
		return NULL;
	}

	vpn = find_active_vpn_connection_by_connection (manager, connection);
	if (vpn) {
		nm_vpn_connection_disconnect (vpn, NM_VPN_CONNECTION_STATE_REASON_USER_DISCONNECTED);
		vpn = NULL;
	}

	service_name = nm_setting_vpn_get_service_type (vpn_setting);
	g_assert (service_name);
	service = g_hash_table_lookup (NM_VPN_MANAGER_GET_PRIVATE (manager)->services, service_name);
	if (!service) {
		g_set_error (error,
		             NM_VPN_MANAGER_ERROR, NM_VPN_MANAGER_ERROR_SERVICE_INVALID,
		             "The VPN service '%s' was not installed.",
		             service_name);
		return NULL;
	}

	return (NMActiveConnection *) nm_vpn_service_activate (service,
	                                                       connection,
	                                                       device,
	                                                       specific_object,
	                                                       user_requested,
	                                                       user_uid,
	                                                       error);
}

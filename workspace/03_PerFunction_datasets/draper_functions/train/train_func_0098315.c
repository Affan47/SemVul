active_connection_state_changed (NMActiveConnection *active,
                                 GParamSpec *pspec,
                                 NMPolicy *policy)
{
	switch (nm_active_connection_get_state (active)) {
	case NM_ACTIVE_CONNECTION_STATE_ACTIVATED:
		if (NM_IS_VPN_CONNECTION (active))
			vpn_connection_activated (policy, NM_VPN_CONNECTION (active));
		break;
	case NM_ACTIVE_CONNECTION_STATE_DEACTIVATED:
		if (NM_IS_VPN_CONNECTION (active))
			vpn_connection_deactivated (policy, NM_VPN_CONNECTION (active));
		break;
	default:
		break;
	}
}

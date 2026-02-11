nm_vpn_connection_fail (NMVPNConnection *connection,
                        NMVPNConnectionStateReason reason)
{
	g_return_if_fail (NM_IS_VPN_CONNECTION (connection));

	nm_vpn_connection_set_vpn_state (connection,
	                                 NM_VPN_CONNECTION_STATE_FAILED,
	                                 reason);
}

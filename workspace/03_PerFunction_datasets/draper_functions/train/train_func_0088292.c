dhcp_request_rx ( struct dhcp_session *dhcp,
			      struct dhcp_packet *dhcppkt,
			      struct sockaddr_in *peer, uint8_t msgtype,
			      struct in_addr server_id ) {
	struct in_addr ip;
	struct settings *parent;
	struct settings *settings;
	int rc;

	DBGC ( dhcp, "DHCP %p %s from %s:%d", dhcp,
	       dhcp_msgtype_name ( msgtype ), inet_ntoa ( peer->sin_addr ),
	       ntohs ( peer->sin_port ) );
	if ( server_id.s_addr != peer->sin_addr.s_addr )
		DBGC ( dhcp, " (%s)", inet_ntoa ( server_id ) );


	ip = dhcppkt->dhcphdr->yiaddr;
	if ( ip.s_addr )
		DBGC ( dhcp, " for %s", inet_ntoa ( ip ) );
	DBGC ( dhcp, "\n" );


	if ( peer->sin_port != htons ( BOOTPS_PORT ) )
		return;
	if ( msgtype  && ( msgtype != DHCPACK ) )
		return;
	if ( server_id.s_addr != dhcp->server.s_addr )
		return;
	if ( ip.s_addr != dhcp->offer.s_addr )
		return;


	dhcp->local.sin_addr = ip;


	parent = netdev_settings ( dhcp->netdev );
	settings = &dhcppkt->settings;
	if ( ( rc = register_settings ( settings, parent,
					DHCP_SETTINGS_NAME ) ) != 0 ) {
		DBGC ( dhcp, "DHCP %p could not register settings: %s\n",
		       dhcp, strerror ( rc ) );
		dhcp_finished ( dhcp, rc );
		return;
	}


	if ( dhcp->proxy_offer  &&
	     ( ! dhcp->no_pxedhcp )  ) {
		if ( dhcp_has_pxeopts ( dhcp->proxy_offer ) ) {


			settings = &dhcp->proxy_offer->settings;
			if ( ( rc = register_settings ( settings, NULL,
					   PROXYDHCP_SETTINGS_NAME ) ) != 0 ) {
				DBGC ( dhcp, "DHCP %p could not register "
				       "proxy settings: %s\n",
				       dhcp, strerror ( rc ) );
				dhcp_finished ( dhcp, rc );
				return;
			}
		} else {

			dhcp_set_state ( dhcp, &dhcp_state_proxy );
			return;
		}
	}


	dhcp_finished ( dhcp, 0 );
}

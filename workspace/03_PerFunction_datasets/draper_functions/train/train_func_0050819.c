main_hall_do_multi_ready()
{
	int error;

	error = psnet_get_network_status();
	switch( error ) {
	case NETWORK_ERROR_NO_TYPE:
		popup( PF_NO_NETWORKING, 1, POPUP_OK, XSTR( "You have not defined your type of Internet connection.  Please run the Launcher, hit the setup button, and go to the Network tab and choose your connection type.", 360));
		break;
	case NETWORK_ERROR_NO_WINSOCK:
		popup( PF_NO_NETWORKING, 1, POPUP_OK, XSTR( "Winsock is not installed.  You must have TCP/IP and Winsock installed to play multiplayer FreeSpace.", 361));
		break;
	case NETWORK_ERROR_NO_PROTOCOL:
		if (Multi_options_g.protocol == NET_TCP) {
			popup( PF_NO_NETWORKING, 1, POPUP_OK, XSTR( "TCP/IP protocol not found.  This protocol is required for multiplayer FreeSpace.", 1602));
		} else {
			Assert(Multi_options_g.protocol == NET_IPX);
			popup( PF_NO_NETWORKING, 1, POPUP_OK, XSTR( "IPX protocol not found.  This protocol is required for multiplayer FreeSpace.", 1603));
		}
		break;
	case NETWORK_ERROR_CONNECT_TO_ISP:
		popup( PF_NO_NETWORKING, 1, POPUP_OK, XSTR( "You have selected Dial Up Networking as your type of connection to the Internet.  You are not currently connected.  You must connect to your ISP before continuing on past this point.", 363));
		break;
	case NETWORK_ERROR_LAN_AND_RAS:
		popup( PF_NO_NETWORKING, 1, POPUP_OK, XSTR( "You have indicated that you use a LAN for networking.  You also appear to be dialed into your ISP.  Please disconnect from your service provider, or choose Dial Up Networking.", 364));
		break;

	case NETWORK_ERROR_NONE:
	default:
		break;
	}


	if ((Multi_options_g.protocol == NET_TCP) && !Tcp_active) {
		if (Tcp_failure_code == WSAEADDRINUSE) {
			popup( PF_NO_NETWORKING, 1, POPUP_OK, XSTR( "You have selected TCP/IP for multiplayer FreeSpace, but the TCP socket is already in use.  Check for another instance and/or use the \"-port <port_num>\" command line option to select an available port.", 1604));
		} else {
			popup( PF_NO_NETWORKING, 1, POPUP_OK, XSTR( "You have selected TCP/IP for multiplayer FreeSpace, but the TCP/IP protocol was not detected on your machine.", 362));
		}
		return;
	}

	if ((Multi_options_g.protocol == NET_IPX) && !Ipx_active) {
		popup( PF_NO_NETWORKING, 1, POPUP_OK, XSTR( "You have selected IPX for multiplayer FreeSpace, but the IPX protocol was not detected on your machine.", 1402));
		return;
	}

	if (error != NETWORK_ERROR_NONE) {
		return;
	}


	if (Multi_connection_speed == CONNECTION_SPEED_NONE) {
		popup( PF_NO_NETWORKING, 1, POPUP_OK, XSTR( "You must define your connection speed.  Please run the Launcher, hit the setup button, and go to the Network tab and choose your connection speed.", 986) );
		return;
	}


	if (Om_tracker_flag) {
		Multi_options_g.protocol = NET_TCP;
		gameseq_post_event(GS_EVENT_PXO);
	} else {

		gameseq_post_event(GS_EVENT_MULTI_JOIN_GAME);
	}


	psnet_use_protocol(Multi_options_g.protocol);
}

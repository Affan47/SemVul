psnet_broadcast( net_addr * who_to, void * data, int len )
{
	if ( Network_status != NETWORK_STATUS_RUNNING ) {
		ml_string("Network ==> Socket not inited in psnet_broadcast");
		return 0;
	}

	if ( !Can_broadcast ) {
		ml_string("Cannot broadcast -- returning without doing anything");
		return 0;
	}

	ubyte broadcast[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};


	switch ( who_to->type ) {
		case NET_IPX:
		case NET_TCP:
			memcpy(who_to->addr, broadcast, 6);
			psnet_send(who_to, data, len);
			break;

	}

	return 1;
}

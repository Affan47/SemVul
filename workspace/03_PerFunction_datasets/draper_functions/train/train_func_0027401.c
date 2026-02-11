gdbudp_configure ( const char *name, struct sockaddr_in *addr ) {
	struct settings *settings;


	netdev_put ( netdev );

	netdev = find_netdev ( name );
	if ( !netdev ) {
		return NULL;
	}


	netdev_get ( netdev );


	source_addr.sin_port = ( addr && addr->sin_port ) ? addr->sin_port : htons ( DEFAULT_PORT );


	if ( addr && addr->sin_addr.s_addr ) {
		source_addr.sin_addr.s_addr = addr->sin_addr.s_addr;
	} else {
		settings = netdev_settings ( netdev );
		fetch_ipv4_setting ( settings, &ip_setting, &source_addr.sin_addr );
		if ( source_addr.sin_addr.s_addr == 0 ) {
			netdev_put ( netdev );
			netdev = NULL;
			return NULL;
		}
	}

	return &udp_gdb_transport;
}

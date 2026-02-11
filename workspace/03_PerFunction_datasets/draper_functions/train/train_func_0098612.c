dhcp_exec ( int argc, char **argv ) {
	static struct option longopts[] = {
		{ "help", 0, NULL, 'h' },
		{ NULL, 0, NULL, 0 },
	};
	const char *netdev_txt;
	struct net_device *netdev;
	int c;
	int rc;


	while ( ( c = getopt_long ( argc, argv, "h", longopts, NULL ) ) >= 0 ){
		switch ( c ) {
		case 'h':

		default:

			dhcp_syntax ( argv );
			return 1;
		}
	}


	if ( optind != ( argc - 1 ) ) {
		dhcp_syntax ( argv );
		return 1;
	}
	netdev_txt = argv[optind];


	netdev = find_netdev ( netdev_txt );
	if ( ! netdev ) {
		printf ( "No such interface: %s\n", netdev_txt );
		return 1;
	}


	if ( ( rc = dhcp ( netdev ) ) != 0 ) {
		printf ( "Could not configure %s: %s\n", netdev->name,
			 strerror ( rc ) );
		return 1;
	}

	return 0;
}

gdbstub_exec ( int argc, char **argv ) {
	static struct option longopts[] = {
		{ "help", 0, NULL, 'h' },
		{ NULL, 0, NULL, 0 },
	};
	const char *trans_name;
	struct gdb_transport *trans;
	int c;


	while ( ( c = getopt_long ( argc, argv, "h", longopts, NULL ) ) >= 0 ){
		switch ( c ) {
		case 'h':

		default:

			gdbstub_syntax ( argv );
			return 1;
		}
	}


	if ( optind == argc ) {
		gdbstub_syntax ( argv );
		return 1;
	}

	trans_name = argv[optind++];


	trans = find_gdb_transport ( trans_name );
	if ( !trans ) {
		printf ( "%s: no such transport (is it compiled in?)\n", trans_name );
		return 1;
	}

	if ( trans->init ) {
		if ( trans->init ( argc - optind, &argv[optind] ) != 0 ) {
			return 1;
		}
	}


	gdbstub_start ( trans );
	return 0;
}

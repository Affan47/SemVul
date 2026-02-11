login_exec ( int argc, char **argv ) {
	int rc;

	if ( argc > 1 ) {
		printf ( "Usage: %s\n"
			 "Prompt for login credentials\n", argv[0] );
		return 1;
	}

	if ( ( rc = login_ui() ) != 0 ) {
		printf ( "Could not set credentials: %s\n",
			 strerror ( rc ) );
		return 1;
	}

	return 0;
}

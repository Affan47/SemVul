gateA20_set ( void ) {
	static char reentry_guard = 0;
	static int a20_method = A20_UNKNOWN;
	unsigned int discard_a;
	unsigned int scp_a;
	int retries = 0;


	if ( reentry_guard )
		return;
	reentry_guard = 1;


	if ( gateA20_is_set ( 0 ) )
		goto out;

	for ( ; retries < A20_MAX_RETRIES ; retries++ ) {
		switch ( a20_method ) {
		case A20_UNKNOWN:
		case A20_INT15:

			__asm__ __volatile__ ( REAL_CODE ( "int $0x15" )
					       : "=a" ( discard_a )
					       : "a" ( Enable_A20 ) );
			if ( gateA20_is_set ( A20_INT15_RETRIES ) ) {
				DBG ( "Enabled gate A20 using BIOS\n" );
				a20_method = A20_INT15;
				goto out;
			}

		case A20_KBC:

			empty_8042();
			outb ( KC_CMD_WOUT, K_CMD );
			empty_8042();
			outb ( KB_SET_A20, K_RDWR );
			empty_8042();
			outb ( KC_CMD_NULL, K_CMD );
			empty_8042();
			if ( gateA20_is_set ( A20_KBC_RETRIES ) ) {
				DBG ( "Enabled gate A20 using "
				      "keyboard controller\n" );
				a20_method = A20_KBC;
				goto out;
			}

		case A20_SCPA:

			scp_a = inb ( SCP_A );
			scp_a &= ~0x01;
			scp_a |= 0x02;
			iodelay();
			outb ( scp_a, SCP_A );
			iodelay();
			if ( gateA20_is_set ( A20_SCPA_RETRIES ) ) {
				DBG ( "Enabled gate A20 using "
				      "Fast Gate A20\n" );
				a20_method = A20_SCPA;
				goto out;
			}
		}
	}


	printf ( "FATAL: Gate A20 stuck\n" );
	while ( 1 ) {}

 out:
	if ( retries )
		DBG ( "%d attempts were required to enable A20\n",
		      ( retries + 1 ) );
	reentry_guard = 0;
}

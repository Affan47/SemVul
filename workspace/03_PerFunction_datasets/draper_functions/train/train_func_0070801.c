state_registerPrefixes( int fd, int itf, Msgs *msgs ){
	Message *m;

	diag( COMPONENT, DIAG_INFO, "State S6: register prefixes" );
	ilmi_state = down;


	if(( config->atmfAddressRegistrationAdminStatus == 1 ) ||
	   ( config->atmfAddressRegistrationAdminStatus == 0 )){
		action_A6( fd, msgs );
		action_A15( fd, msgs );
		action_A7( fd, msgs );
		action_A5( fd, msgs );

		while(( m = wait_for_setresponse( fd, itf, msgs )) == NULL ){
			if( ilmi_errno == ETIMEOUT ){

				action_A15( fd, msgs );
				action_A8( fd, msgs );
				action_A5( fd, msgs );
			} else if( ilmi_errno == ECOLDSTART ){
				return S1;
			}
		}
	} else{
		diag( COMPONENT, DIAG_ERROR,
			"address registration not supported" );
		action_A6( fd, msgs );
		action_A12( fd, msgs );
		action_A7( fd, msgs );
		action_A5( fd, msgs );
	}

	return S9;
}

handle_ilmidiag(int fd, AttPoint *apoint, Config *config) {
	struct sockaddr_un incoming;
	socklen_t inlen = sizeof(incoming);
	struct atm_cirange cir;
	struct ilmi_state ic;
	int newfd = accept(fd, (struct sockaddr *)&incoming, &inlen);

	if (newfd < 0) return -1;


	memset( &ic, 0, sizeof( ic ));
	ic.ilmi_version = 2;
	ic.uni_version = atmfAtmLayerUniVersionValue & 0xff;

	if( get_ci_range( &cir ) < 0 )
		diag( COMPONENT, DIAG_ERROR, "get_ci_range() failed" );
	else{
		if( cir.vpi_bits < config->atmfAtmLayerMaxVpiBits )
			ic.vpi_bits = cir.vpi_bits;
		else ic.vpi_bits = config->atmfAtmLayerMaxVpiBits & 0xff;
		if( cir.vci_bits < config->atmfAtmLayerMaxVciBits )
			ic.vci_bits = cir.vci_bits;
		else ic.vci_bits = config->atmfAtmLayerMaxVciBits & 0xff;
	}

	ic.state = ( ilmi_state == down ) ? 0 : 1;
	if( remsys->sysName.octs ) strncpy( ic.remote_sysname,
		remsys->sysName.octs,
		( remsys->sysName.octetLen < ATM_REMOTE_SYSNAME_LEN )
		? remsys->sysName.octetLen : ATM_REMOTE_SYSNAME_LEN );
	else strncpy( ic.remote_sysname, "(empty)", 7 );
	if( remsys->sysContact.octs ) strncpy( ic.remote_contact,
		remsys->sysContact.octs,
		( remsys->sysContact.octetLen < ATM_REMOTE_CONTACT_LEN )
		? remsys->sysContact.octetLen : ATM_REMOTE_CONTACT_LEN );
	else strncpy( ic.remote_contact, "(empty)", 7 );
	ic.remote_portid = apoint->atmfPortMyIfIdentifier;
	if( apoint->atmfPortMyIfName.octs ) strncpy(
		ic.remote_portname, apoint->atmfPortMyIfName.octs,
		( apoint->atmfPortMyIfName.octetLen < ATM_REMOTE_PORTNAME_LEN )
		? apoint->atmfPortMyIfName.octetLen : ATM_REMOTE_PORTNAME_LEN );
	else strncpy( ic.remote_portname, "(empty)", 7 );

	write(newfd, &ic, sizeof(ic));
	close(newfd);
	exit(0);
}

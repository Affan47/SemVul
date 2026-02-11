nvo_realloc_dhcpopt ( struct dhcp_options *options, size_t len ) {
	struct nvo_block *nvo =
		container_of ( options, struct nvo_block, dhcpopts );
	int rc;


	if ( ! nvo->resize )
		return dhcpopt_no_realloc ( options, len );


	if ( len )
		len += 1;


	if ( ( rc = nvo->resize ( nvo, len ) ) != 0 ) {
		DBGC ( nvo, "NVO %p could not resize to %zd bytes: %s\n",
		       nvo, len, strerror ( rc ) );
		return rc;
	}


	if ( ( rc = nvo_realloc ( nvo, len ) ) != 0 )
		return rc;

	return 0;
}

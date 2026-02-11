nvo_init_dhcpopts ( struct nvo_block *nvo ) {
	uint8_t *options_data;
	size_t options_len;


	options_data = ( nvo->data + 1 );
	options_len = ( nvo->total_len - 1 );


	if ( ( nvo_checksum ( nvo ) != 0 ) || ( options_data[0] == 0 ) ) {
		DBGC ( nvo, "NVO %p has checksum %02x and initial byte %02x; "
		       "assuming empty\n", nvo, nvo_checksum ( nvo ),
		       options_data[0] );
		memset ( nvo->data, 0, nvo->total_len );
	}

	dhcpopt_init ( &nvo->dhcpopts, options_data, options_len );
}

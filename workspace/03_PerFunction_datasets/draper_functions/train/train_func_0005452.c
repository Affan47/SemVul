nvo_save ( struct nvo_block *nvo ) {
	uint8_t *checksum = nvo->data;
	int rc;


	if ( nvo->len > 0 )
		*checksum -= nvo_checksum ( nvo );


	if ( ( rc = nvs_write ( nvo->nvs, nvo->address, nvo->data,
				nvo->len ) ) != 0 ) {
		DBGC ( nvo, "NVO %p could not write %zd bytes at %#04x: %s\n",
		       nvo, nvo->len, nvo->address, strerror ( rc ) );
		return rc;
	}

	DBGC ( nvo, "NVO %p saved to non-volatile storage\n", nvo );
	return 0;
}

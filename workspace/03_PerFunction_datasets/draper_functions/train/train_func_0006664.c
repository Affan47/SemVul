DecodeDBCrlEntry(certDBEntryRevocation *entry, SECItem *dbentry)
{
    unsigned int urlLen;
    int lenDiff;


    if ( dbentry->len < DB_CRL_ENTRY_HEADER_LEN ) {
	PORT_SetError(SEC_ERROR_BAD_DATABASE);
	goto loser;
    }


    entry->derCrl.len = ( ( dbentry->data[0] << 8 ) | dbentry->data[1] );
    urlLen =            ( ( dbentry->data[2] << 8 ) | dbentry->data[3] );
    lenDiff = dbentry->len -
			(entry->derCrl.len + urlLen + DB_CRL_ENTRY_HEADER_LEN);
    if (lenDiff) {
    	if (lenDiff < 0 || (lenDiff & 0xffff) != 0) {
	    PORT_SetError(SEC_ERROR_BAD_DATABASE);
	    goto loser;
	}

	entry->derCrl.len += lenDiff;
    }


    entry->derCrl.data = (unsigned char *)PORT_ArenaAlloc(entry->common.arena,
							 entry->derCrl.len);
    if ( entry->derCrl.data == NULL ) {
	PORT_SetError(SEC_ERROR_NO_MEMORY);
	goto loser;
    }
    PORT_Memcpy(entry->derCrl.data, &dbentry->data[DB_CRL_ENTRY_HEADER_LEN],
	      entry->derCrl.len);


    entry->url = NULL;
    if (urlLen != 0) {
	entry->url = (char *)PORT_ArenaAlloc(entry->common.arena, urlLen);
	if ( entry->url == NULL ) {
	    PORT_SetError(SEC_ERROR_NO_MEMORY);
	    goto loser;
	}
	PORT_Memcpy(entry->url,
	      &dbentry->data[DB_CRL_ENTRY_HEADER_LEN + entry->derCrl.len],
	      urlLen);
    }

    return(SECSuccess);
loser:
    return(SECFailure);
}

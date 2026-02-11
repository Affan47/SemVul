NewDBCertEntry(SECItem *derCert, char *nickname,
	       NSSLOWCERTCertTrust *trust, int flags)
{
    certDBEntryCert *entry;
    PLArenaPool *arena = NULL;
    int nnlen;

    arena = PORT_NewArena( DER_DEFAULT_CHUNKSIZE );

    if ( !arena ) {
	goto loser;
    }

    entry = PORT_ArenaZNew(arena, certDBEntryCert);
    if ( entry == NULL ) {
	goto loser;
    }


    entry->common.arena = arena;
    entry->common.type = certDBEntryTypeCert;
    entry->common.version = CERT_DB_FILE_VERSION;
    entry->common.flags = flags;

    if ( trust ) {
	entry->trust = *trust;
    }

    entry->derCert.data = (unsigned char *)PORT_ArenaAlloc(arena, derCert->len);
    if ( !entry->derCert.data ) {
	goto loser;
    }
    entry->derCert.len = derCert->len;
    PORT_Memcpy(entry->derCert.data, derCert->data, derCert->len);

    nnlen = ( nickname ? strlen(nickname) + 1 : 0 );

    if ( nnlen ) {
	entry->nickname = (char *)PORT_ArenaAlloc(arena, nnlen);
	if ( !entry->nickname ) {
	    goto loser;
	}
	PORT_Memcpy(entry->nickname, nickname, nnlen);

    } else {
	entry->nickname = 0;
    }

    return(entry);

loser:


    if ( arena ) {
	PORT_FreeArena(arena, PR_FALSE);
    }

    PORT_SetError(SEC_ERROR_NO_MEMORY);
    return(0);
}

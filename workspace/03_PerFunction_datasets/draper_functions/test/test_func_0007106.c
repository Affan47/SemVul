DeleteDBSubjectEntry(NSSLOWCERTCertDBHandle *handle, SECItem *derSubject)
{
    SECItem dbkey;
    PLArenaPool *arena = NULL;
    SECStatus rv;

    arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);
    if ( arena == NULL ) {
	goto loser;
    }

    rv = EncodeDBSubjectKey(derSubject, arena, &dbkey);
    if ( rv != SECSuccess ) {
	goto loser;
    }

    rv = DeleteDBEntry(handle, certDBEntryTypeSubject, &dbkey);
    if ( rv == SECFailure ) {
	goto loser;
    }

    PORT_FreeArena(arena, PR_FALSE);
    return(SECSuccess);

loser:
    if ( arena ) {
	PORT_FreeArena(arena, PR_FALSE);
    }

    return(SECFailure);
}

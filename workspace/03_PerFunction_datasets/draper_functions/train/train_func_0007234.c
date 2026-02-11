EncodeDBCertKey(const SECItem *certKey, PLArenaPool *arena, SECItem *dbkey)
{
    unsigned int len = certKey->len + SEC_DB_KEY_HEADER_LEN;
    if (len > NSS_MAX_LEGACY_DB_KEY_SIZE)
	goto loser;
    if (arena) {
	dbkey->data = (unsigned char *)PORT_ArenaAlloc(arena, len);
    } else {
	if (dbkey->len < len) {
	    dbkey->data = (unsigned char *)PORT_Alloc(len);
	}
    }
    dbkey->len = len;
    if ( dbkey->data == NULL ) {
	goto loser;
    }
    PORT_Memcpy(&dbkey->data[SEC_DB_KEY_HEADER_LEN],
	      certKey->data, certKey->len);
    dbkey->data[0] = certDBEntryTypeCert;

    return(SECSuccess);
loser:
    return(SECFailure);
}

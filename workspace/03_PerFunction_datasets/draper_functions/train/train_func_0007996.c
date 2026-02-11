EncodeDBCrlEntry(certDBEntryRevocation *entry, PLArenaPool *arena, SECItem *dbitem)
{
    unsigned int nnlen = 0;
    unsigned char *buf;

    if (entry->url) {
	nnlen = PORT_Strlen(entry->url) + 1;
    }


    dbitem->len = entry->derCrl.len + nnlen
		+ SEC_DB_ENTRY_HEADER_LEN + DB_CRL_ENTRY_HEADER_LEN;

    dbitem->data = (unsigned char *)PORT_ArenaAlloc(arena, dbitem->len);
    if ( dbitem->data == NULL) {
	PORT_SetError(SEC_ERROR_NO_MEMORY);
	goto loser;
    }


    buf = &dbitem->data[SEC_DB_ENTRY_HEADER_LEN];

    buf[0] = (PRUint8)( entry->derCrl.len >> 8 );
    buf[1] = (PRUint8)( entry->derCrl.len      );
    buf[2] = (PRUint8)( nnlen >> 8 );
    buf[3] = (PRUint8)( nnlen      );

    PORT_Memcpy(&buf[DB_CRL_ENTRY_HEADER_LEN], entry->derCrl.data,
	      entry->derCrl.len);

    if (nnlen != 0) {
	PORT_Memcpy(&buf[DB_CRL_ENTRY_HEADER_LEN + entry->derCrl.len],
	      entry->url, nnlen);
    }

    return(SECSuccess);

loser:
    return(SECFailure);
}

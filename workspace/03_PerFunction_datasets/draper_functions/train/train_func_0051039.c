ReadDBCertEntry(NSSLOWCERTCertDBHandle *handle, const SECItem *certKey)
{
    certDBEntryCert *entry;
    SECItem dbkey;
    SECItem dbentry;
    SECStatus rv;
    unsigned char buf[512];

    dbkey.data = buf;
    dbkey.len = sizeof(buf);

    entry = CreateCertEntry();
    if ( entry == NULL ) {
	PORT_SetError(SEC_ERROR_NO_MEMORY);
	goto loser;
    }
    entry->common.arena = NULL;
    entry->common.type = certDBEntryTypeCert;

    rv = EncodeDBCertKey(certKey, NULL, &dbkey);
    if ( rv != SECSuccess ) {
	goto loser;
    }

    rv = ReadDBEntry(handle, &entry->common, &dbkey, &dbentry, NULL);
    if ( rv == SECFailure ) {
	goto loser;
    }

    rv = DecodeDBCertEntry(entry, &dbentry);
    if ( rv != SECSuccess ) {
	goto loser;
    }

    pkcs11_freeStaticData(dbkey.data,buf);
    dbkey.data = NULL;
    return(entry);

loser:
    pkcs11_freeStaticData(dbkey.data,buf);
    dbkey.data = NULL;
    if ( entry ) {
        DestroyDBEntry((certDBEntry *)entry);
    }

    return(NULL);
}

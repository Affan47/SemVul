AddNicknameToPermCert(NSSLOWCERTCertDBHandle *dbhandle,
				NSSLOWCERTCertificate *cert, char *nickname)
{
    certDBEntryCert *entry;
    int rv;

    entry = cert->dbEntry;
    PORT_Assert(entry != NULL);
    if ( entry == NULL ) {
	goto loser;
    }

    pkcs11_freeNickname(entry->nickname,entry->nicknameSpace);
    entry->nickname = NULL;
    entry->nickname = pkcs11_copyNickname(nickname,entry->nicknameSpace,
					sizeof(entry->nicknameSpace));

    rv = WriteDBCertEntry(dbhandle, entry);
    if ( rv ) {
	goto loser;
    }

    pkcs11_freeNickname(cert->nickname,cert->nicknameSpace);
    cert->nickname = NULL;
    cert->nickname = pkcs11_copyNickname(nickname,cert->nicknameSpace,
					sizeof(cert->nicknameSpace));

    return(SECSuccess);

loser:
    return(SECFailure);
}

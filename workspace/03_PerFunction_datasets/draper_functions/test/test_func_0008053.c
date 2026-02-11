DecodeTrustEntry(NSSLOWCERTCertDBHandle *handle, certDBEntryCert *entry,
                 const SECItem *dbKey)
{
    NSSLOWCERTTrust *trust = CreateTrust();
    if (trust == NULL) {
	return trust;
    }
    trust->dbhandle = handle;
    trust->dbEntry = entry;
    trust->dbKey.data = pkcs11_copyStaticData(dbKey->data,dbKey->len,
				trust->dbKeySpace, sizeof(trust->dbKeySpace));
    if (!trust->dbKey.data) {
	PORT_Free(trust);
	return NULL;
    }
    trust->dbKey.len = dbKey->len;

    trust->trust = &entry->trust;
    trust->derCert = &entry->derCert;

    return(trust);
}

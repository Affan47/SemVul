lg_getSMime(LGObjectCache *obj)
{
    certDBEntrySMime *entry;
    NSSLOWCERTCertDBHandle *certHandle;

    if (obj->objclass != CKO_NSS_SMIME) {
	return NULL;
    }
    if (obj->objectInfo) {
	return (certDBEntrySMime *)obj->objectInfo;
    }

    certHandle = lg_getCertDB(obj->sdb);
    if (!certHandle) {
	return NULL;
    }
    entry = nsslowcert_ReadDBSMimeEntry(certHandle, (char *)obj->dbKey.data);
    obj->objectInfo = (void *)entry;
    obj->infoFree = (LGFreeFunc) nsslowcert_DestroyDBEntry;
    return entry;
}

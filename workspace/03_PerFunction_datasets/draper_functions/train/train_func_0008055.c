sftkdb_decrypt_stub(SDB *sdb, SECItem *cipherText, SECItem **plainText)
{
    SFTKDBHandle *handle = sdb->app_private;
    SECStatus rv;
    SECItem *oldKey = NULL;

    if (handle == NULL) {
	return SECFailure;
    }


    oldKey = handle->oldKey;
    if (handle->type != SFTK_KEYDB_TYPE) {
	handle = handle->peerDB;
    }


    if (handle == NULL || handle->passwordLock == NULL) {
	return SECFailure;
    }

    PZ_Lock(handle->passwordLock);
    if (handle->passwordKey.data == NULL) {
	PZ_Unlock(handle->passwordLock);

	return SECFailure;
    }
    rv = sftkdb_DecryptAttribute( oldKey ? oldKey : &handle->passwordKey,
		cipherText, plainText);
    PZ_Unlock(handle->passwordLock);

    return rv;
}

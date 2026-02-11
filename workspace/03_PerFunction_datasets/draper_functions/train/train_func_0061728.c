sftkdb_encrypt_stub(PLArenaPool *arena, SDB *sdb, SECItem *plainText,
		    SECItem **cipherText)
{
    SFTKDBHandle *handle = sdb->app_private;
    SECStatus rv;

    if (handle == NULL) {
	return SECFailure;
    }


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

    rv = sftkdb_EncryptAttribute(arena,
	handle->newKey?handle->newKey:&handle->passwordKey,
	plainText, cipherText);
    PZ_Unlock(handle->passwordLock);

    return rv;
}

sftkdb_FreeUpdatePasswordKey(SFTKDBHandle *handle)
{
    SECItem *key = NULL;


    if (!handle) {
	return;
    }


    if (handle->type == SFTK_CERTDB_TYPE) {
	return;
    }

    PZ_Lock(handle->passwordLock);
    if (handle->updatePasswordKey) {
	key = handle->updatePasswordKey;
	handle->updatePasswordKey = NULL;
    }
    PZ_Unlock(handle->passwordLock);

    if (key) {
	SECITEM_ZfreeItem(key, PR_TRUE);
    }

    return;
}

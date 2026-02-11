NSC_Login(CK_SESSION_HANDLE hSession, CK_USER_TYPE userType,
				    CK_CHAR_PTR pPin, CK_ULONG ulPinLen)
{
    SFTKSlot *slot;
    SFTKSession *session;
    SFTKDBHandle *handle;
    CK_FLAGS sessionFlags;
    SECStatus rv;
    CK_RV crv;
    char pinStr[SFTK_MAX_PIN+1];
    PRBool tokenRemoved = PR_FALSE;

    CHECK_FORK();


    slot = sftk_SlotFromSessionHandle(hSession);
    if (slot == NULL) {
	return CKR_SESSION_HANDLE_INVALID;
    }


    session = sftk_SessionFromHandle(hSession);
    if (session == NULL) {
	return CKR_SESSION_HANDLE_INVALID;
    }
    sessionFlags = session->info.flags;
    sftk_FreeSession(session);
    session = NULL;


    if (slot->slotID == NETSCAPE_SLOT_ID) {
	 return CKR_USER_TYPE_INVALID;
    }

    if (slot->isLoggedIn) return CKR_USER_ALREADY_LOGGED_IN;
    if (!slot->needLogin) {
        return ulPinLen ? CKR_PIN_INCORRECT : CKR_OK;
    }
    slot->ssoLoggedIn = PR_FALSE;

    if (ulPinLen > SFTK_MAX_PIN) return CKR_PIN_LEN_RANGE;


    PORT_Memcpy(pinStr,pPin,ulPinLen);
    pinStr[ulPinLen] = 0;

    handle = sftk_getKeyDB(slot);
    if (handle == NULL) {
	 return CKR_USER_TYPE_INVALID;
    }


    rv = sftkdb_HasPasswordSet(handle);
    if (rv == SECFailure) {


	if (((userType == CKU_SO) && (sessionFlags & CKF_RW_SESSION))

					|| (slot->slotID == FIPS_SLOT_ID)) {

	    if (ulPinLen == 0) {
		sftkdb_ClearPassword(handle);
    		PZ_Lock(slot->slotLock);
		slot->isLoggedIn = PR_TRUE;
		slot->ssoLoggedIn = (PRBool)(userType == CKU_SO);
		PZ_Unlock(slot->slotLock);
		sftk_update_all_states(slot);
		crv = CKR_OK;
		goto done;
	    }
	    crv = CKR_PIN_INCORRECT;
	    goto done;
	}
	crv = CKR_USER_TYPE_INVALID;
	goto done;
    }


    if (userType != CKU_USER) {
	crv = CKR_USER_TYPE_INVALID;
	goto done;
    }


    PR_Lock(slot->pwCheckLock);
    rv = sftkdb_CheckPassword(handle,pinStr, &tokenRemoved);
    if (tokenRemoved) {
	sftk_CloseAllSessions(slot, PR_FALSE);
    }
    if ((rv != SECSuccess) && (slot->slotID == FIPS_SLOT_ID)) {
	PR_Sleep(loginWaitTime);
    }
    PR_Unlock(slot->pwCheckLock);
    if (rv == SECSuccess) {
	PZ_Lock(slot->slotLock);


	slot->isLoggedIn = sftkdb_PWCached(handle) == SECSuccess ?
		PR_TRUE : PR_FALSE;
	PZ_Unlock(slot->slotLock);

 	sftk_freeDB(handle);
	handle = NULL;


	sftk_update_all_states(slot);
	return CKR_OK;
    }

    crv = CKR_PIN_INCORRECT;
done:
    if (handle) {
	sftk_freeDB(handle);
    }
    return crv;
}

NSC_InitPIN(CK_SESSION_HANDLE hSession,
    					CK_CHAR_PTR pPin, CK_ULONG ulPinLen)
{
    SFTKSession *sp = NULL;
    SFTKSlot *slot;
    SFTKDBHandle *handle = NULL;
    char newPinStr[SFTK_MAX_PIN+1];
    SECStatus rv;
    CK_RV crv = CKR_SESSION_HANDLE_INVALID;
    PRBool tokenRemoved = PR_FALSE;

    CHECK_FORK();

    sp = sftk_SessionFromHandle(hSession);
    if (sp == NULL) {
	goto loser;
    }

    slot = sftk_SlotFromSession(sp);
    if (slot == NULL) {
	goto loser;
    }

    handle = sftk_getKeyDB(slot);
    if (handle == NULL) {
	crv = CKR_PIN_LEN_RANGE;
	goto loser;
    }


    if (sp->info.state != CKS_RW_SO_FUNCTIONS) {
	crv = CKR_USER_NOT_LOGGED_IN;
	goto loser;
    }

    sftk_FreeSession(sp);
    sp = NULL;


    if (ulPinLen > SFTK_MAX_PIN) {
	crv = CKR_PIN_LEN_RANGE;
	goto loser;
    }
    if (ulPinLen < (CK_ULONG)slot->minimumPinLen) {
	crv = CKR_PIN_LEN_RANGE;
	goto loser;
    }

    if (sftkdb_HasPasswordSet(handle) != SECFailure) {
	crv = CKR_DEVICE_ERROR;
	goto loser;
    }


    PORT_Memcpy(newPinStr, pPin, ulPinLen);
    newPinStr[ulPinLen] = 0;


    rv = sftkdb_ChangePassword(handle, NULL, newPinStr, &tokenRemoved);
    if (tokenRemoved) {
	sftk_CloseAllSessions(slot, PR_FALSE);
    }
    sftk_freeDB(handle);
    handle = NULL;


    if (rv == SECSuccess) {
	if (ulPinLen == 0) slot->needLogin = PR_FALSE;
	return CKR_OK;
    }
    crv = CKR_PIN_INCORRECT;

loser:
    if (sp) {
	sftk_FreeSession(sp);
    }
    if (handle) {
	sftk_freeDB(handle);
    }
    return crv;
}

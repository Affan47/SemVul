PK11_VerifyRecover(SECKEYPublicKey *key, const SECItem *sig,
		   SECItem *dsig, void *wincx)
{
    PK11SlotInfo *slot = key->pkcs11Slot;
    CK_OBJECT_HANDLE id = key->pkcs11ID;
    CK_MECHANISM mech = {0, NULL, 0 };
    PRBool owner = PR_TRUE;
    CK_SESSION_HANDLE session;
    CK_ULONG len;
    CK_RV crv;

    mech.mechanism = PK11_MapSignKeyType(key->keyType);

    if (slot == NULL) {
	slot = PK11_GetBestSlotWithAttributes(mech.mechanism,
				CKF_VERIFY_RECOVER,0,wincx);
	if (slot == NULL) {
	    	PORT_SetError( SEC_ERROR_NO_MODULE );
		return SECFailure;
	}
	id = PK11_ImportPublicKey(slot,key,PR_FALSE);
    } else {
	PK11_ReferenceSlot(slot);
    }

    if (id == CK_INVALID_HANDLE) {
	PK11_FreeSlot(slot);
	PORT_SetError( SEC_ERROR_BAD_KEY );
	return SECFailure;
    }

    session = pk11_GetNewSession(slot,&owner);
    if (!owner || !(slot->isThreadSafe)) PK11_EnterSlotMonitor(slot);
    crv = PK11_GETTAB(slot)->C_VerifyRecoverInit(session,&mech,id);
    if (crv != CKR_OK) {
	if (!owner || !(slot->isThreadSafe)) PK11_ExitSlotMonitor(slot);
	pk11_CloseSession(slot,session,owner);
	PORT_SetError( PK11_MapError(crv) );
	PK11_FreeSlot(slot);
	return SECFailure;
    }
    len = dsig->len;
    crv = PK11_GETTAB(slot)->C_VerifyRecover(session,sig->data,
						sig->len, dsig->data, &len);
    if (!owner || !(slot->isThreadSafe)) PK11_ExitSlotMonitor(slot);
    pk11_CloseSession(slot,session,owner);
    dsig->len = len;
    if (crv != CKR_OK) {
	PORT_SetError( PK11_MapError(crv) );
	PK11_FreeSlot(slot);
	return SECFailure;
    }
    PK11_FreeSlot(slot);
    return SECSuccess;
}

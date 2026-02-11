PK11_SymKeyFromHandle(PK11SlotInfo *slot, PK11SymKey *parent, PK11Origin origin,
    CK_MECHANISM_TYPE type, CK_OBJECT_HANDLE keyID, PRBool owner, void *wincx)
{
    PK11SymKey *symKey;
    PRBool needSession = !(owner && parent);

    if (keyID == CK_INVALID_HANDLE) {
	return NULL;
    }

    symKey = pk11_CreateSymKey(slot, type, owner, needSession, wincx);
    if (symKey == NULL) {
	return NULL;
    }

    symKey->objectID = keyID;
    symKey->origin = origin;


    if (!needSession) {
	symKey->sessionOwner = PR_FALSE;
	symKey->session = parent->session;
	symKey->parent = PK11_ReferenceSymKey(parent);


	PORT_Assert(parent->session != CK_INVALID_SESSION);
	if (parent->session == CK_INVALID_SESSION) {
	    PK11_FreeSymKey(symKey);
	    PORT_SetError(SEC_ERROR_LIBRARY_FAILURE);
	    return NULL;
	}
    }

    return symKey;
}

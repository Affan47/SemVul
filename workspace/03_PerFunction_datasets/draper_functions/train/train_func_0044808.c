PK11_MatchItem(PK11SlotInfo *slot, CK_OBJECT_HANDLE searchID,
				 		CK_OBJECT_CLASS matchclass)
{
    CK_ATTRIBUTE theTemplate[] = {
	{ CKA_ID, NULL, 0 },
	{ CKA_CLASS, NULL, 0 }
    };

    CK_ATTRIBUTE *keyclass = &theTemplate[1];
    int tsize = sizeof(theTemplate)/sizeof(theTemplate[0]);

    CK_OBJECT_HANDLE peerID;
    CK_OBJECT_HANDLE parent;
    PLArenaPool *arena;
    CK_RV crv;


    arena = PORT_NewArena( DER_DEFAULT_CHUNKSIZE);
    if (arena == NULL) return CK_INVALID_HANDLE;

    crv = PK11_GetAttributes(arena,slot,searchID,theTemplate,tsize);
    if (crv != CKR_OK) {
	PORT_FreeArena(arena,PR_FALSE);
	PORT_SetError( PK11_MapError(crv) );
	return CK_INVALID_HANDLE;
    }

    if ((theTemplate[0].ulValueLen == 0) || (theTemplate[0].ulValueLen == -1)) {
	PORT_FreeArena(arena,PR_FALSE);
	if (matchclass == CKO_CERTIFICATE)
	    PORT_SetError(SEC_ERROR_BAD_KEY);
	else
	    PORT_SetError(SEC_ERROR_NO_KEY);
	return CK_INVALID_HANDLE;
     }


    parent = *(CK_OBJECT_CLASS *)(keyclass->pValue);
    *(CK_OBJECT_CLASS *)(keyclass->pValue) = matchclass;

    peerID = pk11_FindObjectByTemplate(slot,theTemplate,tsize);
    PORT_FreeArena(arena,PR_FALSE);

    return peerID;
}

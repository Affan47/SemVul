PK11_FindFixedKey(PK11SlotInfo *slot, CK_MECHANISM_TYPE type, SECItem *keyID,
								void *wincx)
{
    CK_ATTRIBUTE findTemp[4];
    CK_ATTRIBUTE *attrs;
    CK_BBOOL ckTrue = CK_TRUE;
    CK_OBJECT_CLASS keyclass = CKO_SECRET_KEY;
    int tsize = 0;
    CK_OBJECT_HANDLE key_id;

    attrs = findTemp;
    PK11_SETATTRS(attrs, CKA_CLASS, &keyclass, sizeof(keyclass)); attrs++;
    PK11_SETATTRS(attrs, CKA_TOKEN, &ckTrue, sizeof(ckTrue)); attrs++;
    if (keyID) {
        PK11_SETATTRS(attrs, CKA_ID, keyID->data, keyID->len); attrs++;
    }
    tsize = attrs - findTemp;
    PORT_Assert(tsize <= sizeof(findTemp)/sizeof(CK_ATTRIBUTE));

    key_id = pk11_FindObjectByTemplate(slot,findTemp,tsize);
    if (key_id == CK_INVALID_HANDLE) {
	return NULL;
    }
    return PK11_SymKeyFromHandle(slot, NULL, PK11_OriginDerive, type, key_id,
		 				PR_FALSE, wincx);
}

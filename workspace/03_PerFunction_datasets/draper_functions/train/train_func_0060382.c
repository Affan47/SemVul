pk11_GetLowLevelKeyFromHandle(PK11SlotInfo *slot, CK_OBJECT_HANDLE handle)
{
    CK_ATTRIBUTE theTemplate[] = {
	{ CKA_ID, NULL, 0 },
    };
    int tsize = sizeof(theTemplate)/sizeof(theTemplate[0]);
    CK_RV crv;
    SECItem *item;

    item = SECITEM_AllocItem(NULL, NULL, 0);

    if (item == NULL) {
	return NULL;
    }

    crv = PK11_GetAttributes(NULL,slot,handle,theTemplate,tsize);
    if (crv != CKR_OK) {
	SECITEM_FreeItem(item,PR_TRUE);
	PORT_SetError( PK11_MapError(crv) );
	return NULL;
    }

    item->data = (unsigned char*) theTemplate[0].pValue;
    item->len =theTemplate[0].ulValueLen;

    return item;
}

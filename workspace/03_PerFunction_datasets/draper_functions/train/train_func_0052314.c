sftkdb_lookupObject(SDB *db, CK_OBJECT_CLASS objectType,
		 CK_OBJECT_HANDLE *id, CK_ATTRIBUTE *ptemplate, CK_ULONG len)
{
    CK_ATTRIBUTE findTemplate[3];
    CK_ULONG count = 1;
    CK_ULONG objCount = 0;
    SDBFind *find = NULL;
    unsigned char objTypeData[SDB_ULONG_SIZE];
    CK_RV crv;

    *id = CK_INVALID_HANDLE;
    if (objectType == CKO_NSS_CRL) {
	return CKR_OK;
    }
    crv = sftkdb_getFindTemplate(objectType, objTypeData,
			findTemplate, &count, ptemplate, len);

    if (crv == CKR_OBJECT_HANDLE_INVALID) {


	return CKR_OK;
    }
    if (crv != CKR_OK) {
	return crv;
    }


    crv = (*db->sdb_FindObjectsInit)(db, findTemplate, count, &find);
    if (crv != CKR_OK) {
	return crv;
    }
    (*db->sdb_FindObjects)(db, find, id, 1, &objCount);
    (*db->sdb_FindObjectsFinal)(db, find);

    if (objCount == 0) {
	*id = CK_INVALID_HANDLE;
    }
    return CKR_OK;
}

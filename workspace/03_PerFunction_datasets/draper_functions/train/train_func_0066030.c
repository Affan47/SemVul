sftk_updateMacs(PLArenaPool *arena, SFTKDBHandle *handle,
		       CK_OBJECT_HANDLE id, SECItem *newKey)
{
    CK_RV crv = CKR_OK;
    CK_RV crv2;
    CK_ATTRIBUTE authAttrs[] = {
	{CKA_MODULUS, NULL, 0},
	{CKA_PUBLIC_EXPONENT, NULL, 0},
	{CKA_CERT_SHA1_HASH, NULL, 0},
	{CKA_CERT_MD5_HASH, NULL, 0},
	{CKA_TRUST_SERVER_AUTH, NULL, 0},
	{CKA_TRUST_CLIENT_AUTH, NULL, 0},
	{CKA_TRUST_EMAIL_PROTECTION, NULL, 0},
	{CKA_TRUST_CODE_SIGNING, NULL, 0},
	{CKA_TRUST_STEP_UP_APPROVED, NULL, 0},
	{CKA_NSS_OVERRIDE_EXTENSIONS, NULL, 0},
    };
    CK_ULONG authAttrCount = sizeof(authAttrs)/sizeof(CK_ATTRIBUTE);
    int i, count;
    SFTKDBHandle *keyHandle = handle;
    SDB *keyTarget = NULL;

    id &= SFTK_OBJ_ID_MASK;

    if (handle->type != SFTK_KEYDB_TYPE) {
	keyHandle = handle->peerDB;
    }

    if (keyHandle == NULL) {
	return CKR_OK;
    }


    keyTarget = SFTK_GET_SDB(keyHandle);
    if ((keyTarget->sdb_flags &SDB_HAS_META) == 0) {
	return CKR_OK;
    }


    crv2 = sftkdb_GetAttributeValue(handle, id, authAttrs, authAttrCount);
    count = 0;

    for (i=0; i < authAttrCount; i++) {
	if ((authAttrs[i].ulValueLen == -1) || (authAttrs[i].ulValueLen == 0)){
	    continue;
	}
	count++;
        authAttrs[i].pValue = PORT_ArenaAlloc(arena,authAttrs[i].ulValueLen);
	if (authAttrs[i].pValue == NULL) {
	    crv = CKR_HOST_MEMORY;
	    break;
	}
    }


    if (count == 0) {
	return CKR_OK;
    }

    crv = sftkdb_GetAttributeValue(handle, id, authAttrs, authAttrCount);


    for (i=0; i < authAttrCount; i++) {
	SECItem *signText;
	SECItem plainText;
	SECStatus rv;

	if ((authAttrs[i].ulValueLen == -1) || (authAttrs[i].ulValueLen == 0)){
	    continue;
	}

	plainText.data = authAttrs[i].pValue;
	plainText.len = authAttrs[i].ulValueLen;
	rv = sftkdb_SignAttribute(arena, newKey, id,
			authAttrs[i].type, &plainText, &signText);
	if (rv != SECSuccess) {
	    return CKR_GENERAL_ERROR;
	}
	rv = sftkdb_PutAttributeSignature(handle, keyTarget, id,
				authAttrs[i].type, signText);
	if (rv != SECSuccess) {
	    return CKR_GENERAL_ERROR;
	}
    }

    return CKR_OK;
}

generateWrappingKey( void)
{
	RCODE						rc = FERR_OK;

#ifndef FLM_USE_NICI
	rc = RC_SET( FERR_UNSUPPORTED_FEATURE);
	goto Exit;
#else
	NICI_CC_HANDLE			context = 0;
	NICI_ALGORITHM			algorithm;
	NICI_ATTRIBUTE			keyAttr[6];
	FLMUINT8					keySizeChanged;
	FLMBYTE					oid_des3[] = {IDV_DES_EDE3_CBC_IV8};
	FLMUINT					uiIndx;


	if( CCS_CreateContext(0, &context) != 0)
	{
		rc = RC_SET( FERR_NICI_CONTEXT);
		goto Exit;
	}


	algorithm.algorithm = oid_des3;
	algorithm.parameterLen = 0;


	uiIndx = 0;
	keyAttr[uiIndx].type = NICI_A_KEY_TYPE;
	keyAttr[uiIndx].u.f.hasValue = 1;
	keyAttr[uiIndx].u.f.value = NICI_K_DES3X;
	keyAttr[uiIndx].u.f.valueInfo = 0;

	uiIndx++;
	keyAttr[uiIndx].type = NICI_A_KEY_FORMAT;
	keyAttr[uiIndx].u.v.valuePtr = oid_des3;
	keyAttr[uiIndx].u.v.valueLen = sizeof( oid_des3);
	keyAttr[uiIndx].u.v.valueInfo = 0;

	uiIndx++;
	keyAttr[uiIndx].type = NICI_A_KEY_USAGE;
	keyAttr[uiIndx].u.f.hasValue = 1;
	keyAttr[uiIndx].u.f.value = NICI_F_WRAP | NICI_F_UNWRAP | NICI_F_KM_ENCRYPT | NICI_F_KM_DECRYPT | NICI_F_EXTRACT;
	keyAttr[uiIndx].u.f.valueInfo = 0;

	uiIndx++;
	keyAttr[uiIndx].type = NICI_A_KEY_SIZE;
	keyAttr[uiIndx].u.f.hasValue = 1;
	keyAttr[uiIndx].u.f.value = 168;
	keyAttr[uiIndx].u.f.valueInfo = 0;

	uiIndx++;
	keyAttr[uiIndx].type = NICI_A_GLOBAL;
	keyAttr[uiIndx].u.f.hasValue = 1;
	keyAttr[uiIndx].u.f.value = N_TRUE;
	keyAttr[uiIndx].u.f.valueInfo = 0;

	uiIndx++;
	keyAttr[uiIndx].type = NICI_A_CLASS;
	keyAttr[uiIndx].u.f.hasValue = 1;
	keyAttr[uiIndx].u.f.value = NICI_O_SECRET_KEY;
	keyAttr[uiIndx].u.f.valueInfo = 0;


	if( CCS_GenerateKey( context, &algorithm, keyAttr, 6,
		(NICI_BBOOL *)&keySizeChanged, &m_keyHandle, NICI_H_INVALID) != 0)
	{
		rc = RC_SET( FERR_NICI_GENKEY_FAILED);
		goto Exit;
	}


	if (CCS_GetRandom( context, m_pucIV, IV_SZ) != 0)
	{
		rc = RC_SET( FERR_NICI_BAD_RANDOM);
		goto Exit;
	}


	m_bKeyIsWrappingKey = TRUE;
	CCS_DestroyContext(context);

#endif

Exit:

	return(rc);

}

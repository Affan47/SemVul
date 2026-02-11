constructRecord(
	FLMUINT				uiDrn,
	FLMUINT				uiContainer,
	FlmRecord **		ppRec,
	HFDB					hDb)
{
	RCODE					rc = FERR_OK;
	FlmRecord *			pRec;
	char					szTmp[ 128];
	char *				pTmp;
	FLMUINT				uiFieldCount;
	FLMUINT				uiFieldCounter;
	char *				pszFldValue = NULL;

	flmAssert( ppRec);


	if( (pRec = f_new FlmRecord) == NULL)
	{
		rc = RC_SET( FERR_MEM);
		goto Exit;
	}

	pRec->setID( uiDrn);
	pRec->setContainerID( uiContainer);

	pTmp = &szTmp[ 0];

	getFormValueByName( "FieldCount",
			&pTmp, sizeof( szTmp), NULL);

	if (szTmp[ 0])
	{
		uiFieldCount = f_atoud( szTmp);
	}
	else
	{
		rc = RC_SET( FERR_INVALID_PARM);
		printErrorPage( rc, TRUE, "Field Count missing or invalid");
		goto Exit;
	}


	for ( uiFieldCounter = 0; uiFieldCounter < uiFieldCount; uiFieldCounter++)
	{

		FLMUINT				uiLevel;
		FLMUINT				uiType;
		FLMUINT				uiTag;
		void *				pvField = NULL;

		if (RC_BAD( rc = extractFieldInfo( uiFieldCounter, &pszFldValue,
								&uiLevel, &uiType, &uiTag)))
		{
			printErrorPage( rc, TRUE, "Error occurred retrieving field data from form");
			goto Exit;
		}


		if (RC_BAD( rc = pRec->insertLast( uiLevel, uiTag, uiType, &pvField)))
		{
			printErrorPage( rc, TRUE, "Error occurred inserting field into record");
			goto Exit;
		}


		switch( uiType)
		{
			case FLM_TEXT_TYPE:
				{

					rc = storeUnicodeField( pRec, pvField, pszFldValue);
					break;
				}
			case FLM_NUMBER_TYPE:
				{

					rc = storeNumberField( pRec, pvField, pszFldValue);
					break;
				}
			case FLM_BINARY_TYPE:
				{

					rc = storeBinaryField( pRec, pvField, pszFldValue);
					break;
				}
			case FLM_CONTEXT_TYPE:
				{

					if (pszFldValue && *pszFldValue != '\0')
					{
						rc = pRec->setRecPointer( pvField,
							(unsigned long)f_atoud( pszFldValue));
					}
					break;
				}
			case FLM_BLOB_TYPE:
				{

					rc = storeBlobField( pRec, pvField, pszFldValue, hDb);
					break;
				}
		}

		if (RC_BAD( rc))
		{
			goto Exit;
		}
		f_free( &pszFldValue);
	}


Exit:

	if (RC_BAD(rc))
	{
		if (pRec)
		{
			pRec->Release();
			pRec = NULL;
		}
	}

	if (pszFldValue)
	{
		f_free( &pszFldValue);
	}

	*ppRec = pRec;


	return( rc);
}

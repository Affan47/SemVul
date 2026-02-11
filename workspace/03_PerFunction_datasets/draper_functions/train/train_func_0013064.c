setNative(
	void *			pvField,
	const char *	pszString,
	FLMUINT			uiEncId)
{
	RCODE				rc = FERR_OK;
	FLMBYTE *		pucData;
	FLMUINT			uiBufLen;
	FLMUINT			uiEncDataLen = 0;
	FLMUINT			uiEncFlags = 0;

	if( isReadOnly() || isCached())
	{
		flmAssert( 0);
		rc = RC_SET( FERR_FAILURE);
		goto Exit;
	}

	if( !pszString || *pszString == 0)
	{


		if( RC_BAD( rc = getNewDataPtr( getFieldPointer( pvField), FLM_TEXT_TYPE,
			0, 0, 0, 0, &pucData, NULL)))
		{
			goto Exit;
		}
	}
	else
	{
		uiBufLen = FlmGetNativeStorageLength( pszString);

		if( uiEncId)
		{


			if( uiBufLen % 16)
			{
				uiEncDataLen = uiBufLen + (16 - (uiBufLen % 16));
			}
			else
			{
				uiEncDataLen = uiBufLen;
			}

			uiEncFlags = FLD_HAVE_DECRYPTED_DATA;
		}

		if( RC_BAD( rc = getNewDataPtr( getFieldPointer( pvField), FLM_TEXT_TYPE,
			uiBufLen, uiEncDataLen, uiEncId, uiEncFlags, &pucData, NULL)))
		{
			goto Exit;
		}

		if( RC_BAD( rc = FlmNative2Storage( pszString, 0, &uiBufLen, pucData)))
		{
			goto Exit;
		}
	}

Exit:

	return( rc);
}

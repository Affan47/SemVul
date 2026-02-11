setBlob(
	void *			pvField,
	FlmBlob *		pBlob,
	FLMUINT			uiEncId)
{
	RCODE				rc = FERR_OK;
	FLMBYTE *		pucData;
	FLMUINT			uiDataLen = ((FlmBlobImp *)pBlob)->getDataLength();
	FLMUINT			uiEncDataLen = 0;
	FLMUINT			uiEncFlags = 0;

	if( isReadOnly() || isCached())
	{
		flmAssert( 0);
		rc = RC_SET( FERR_FAILURE);
		goto Exit;
	}

	if( !uiDataLen)
	{


		if( RC_BAD( rc = getNewDataPtr( getFieldPointer( pvField), FLM_BLOB_TYPE,
			0, 0, 0, 0, &pucData, NULL)))
		{
			goto Exit;
		}
	}
	else
	{
		if( uiEncId)
		{


			if( uiDataLen % 16)
			{
				uiEncDataLen = uiDataLen + (16 - (uiDataLen % 16));
			}
			else
			{
				uiEncDataLen = uiDataLen;
			}

			uiEncFlags = FLD_HAVE_DECRYPTED_DATA;
		}

		if( RC_BAD( rc = getNewDataPtr( getFieldPointer( pvField),
			FLM_BLOB_TYPE, uiDataLen, uiEncDataLen, uiEncId, uiEncFlags,
			&pucData, NULL)))
		{
			goto Exit;
		}

		f_memcpy( pucData, ((FlmBlobImp *)pBlob)->getDataPtr(), uiDataLen);
	}

Exit:

	return( rc);
}

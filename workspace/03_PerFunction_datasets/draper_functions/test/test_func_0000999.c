getBinary(
	void *		pvField,
	void *		pvBuf,
	FLMUINT *	puiBufLen)
{
	RCODE				rc = FERR_OK;
	FlmField *		pField = getFieldPointer( pvField);

	if( !pField)
	{
		rc = RC_SET( FERR_NOT_FOUND);
		goto Exit;
	}

	if (isEncryptedField( pField) &&
			!(getEncFlags( pField) & FLD_HAVE_DECRYPTED_DATA))
	{
		rc = RC_SET( FERR_ENCRYPTION_UNAVAILABLE);
		goto Exit;
	}

	*puiBufLen = f_min( (*puiBufLen), getFieldDataLength( pField));
	f_memcpy( pvBuf, getDataPtr( pField), *puiBufLen);

Exit:

	return( rc);
}

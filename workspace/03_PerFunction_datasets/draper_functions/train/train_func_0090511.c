getEncFlags(
	FlmField *			pField)
{
	FLMBYTE *	pucBuffer;

	if (!isEncryptedField( pField))
	{
		flmAssert( 0);
		return( 0);
	}

	pucBuffer = getDataBufPtr() + pField->ui32DataOffset;

	return( (FLMUINT)pucBuffer[ FLD_ENC_FLAGS_OFFSET]);
}

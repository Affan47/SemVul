writeSignedNumber(
	FLMUINT		uiTag,
	FLMINT64		i64Number)
{
	RCODE			rc = FERR_OK;

	if( RC_BAD( rc = writeUnsignedNumber( uiTag, (FLMUINT64)i64Number)))
	{
		goto Exit;
	}

Exit:

	return( rc);
}

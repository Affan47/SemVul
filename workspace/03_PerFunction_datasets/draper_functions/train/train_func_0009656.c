fqOpUSMinus(
	FQATOM *	pLValue,
	FQATOM *	pRValue,
	FQATOM *	pResult)
{
	FLMUINT64	ui64Left = fqGetUInt64( pLValue);
	FLMINT64		i64Right = fqGetInt64( pRValue);
	FLMUINT64	ui64Result;
	FLMINT64		i64Result;

	if (i64Right < 0)
	{
		if (i64Right == FLM_MIN_INT64)
		{
			ui64Result = ui64Left + (FLMUINT64)FLM_MAX_INT64 + 1;
		}
		else
		{
			i64Right = -i64Right;
			ui64Result = ui64Left + (FLMUINT64)i64Right;
		}
		setUnsignedResult( ui64Result, pResult);
	}
	else
	{
		if( ui64Left >= (FLMUINT64)i64Right)
		{
			ui64Result = ui64Left - (FLMUINT64)i64Right;
			setUnsignedResult( ui64Result, pResult);
		}
		else
		{
			i64Result = -((FLMINT64)(i64Right - (FLMINT64)ui64Left));
			setSignedResult( i64Result, pResult);
		}
	}
}

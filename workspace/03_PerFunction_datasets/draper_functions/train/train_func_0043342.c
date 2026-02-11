FlmINT2Storage(
	FLMINT		iNum,
	FLMUINT *	puiBufLength,
	FLMBYTE *	pBuf)
{
	FLMUINT		uiNum;
	FLMBYTE		ucNibStk[ F_MAX_NUM64_BUF + 1];
	FLMBYTE *	pucNibStk;
	FLMBOOL		bNegFlag;
#ifdef FLM_DEBUG
	FLMBYTE *	pucNibStkEnd = &ucNibStk[ sizeof( ucNibStk)];
#endif

	flmAssert( *puiBufLength >= F_MAX_NUM_BUF);

	pucNibStk = &ucNibStk[ 1];
	*pucNibStk++ = 0x0F;

	if (iNum < 0)
	{
		bNegFlag = TRUE;
		if (iNum == FLM_MIN_INT)
		{
			uiNum = (FLMUINT)(FLM_MAX_INT) + 1;
		}
		else
		{
			uiNum = (FLMUINT)(-iNum);
		}
	}
	else
	{
		bNegFlag = FALSE;
		uiNum = (FLMUINT)iNum;
	}

	while( uiNum >= 10)
	{
		*pucNibStk++ = (FLMBYTE)(uiNum % 10);
		uiNum /= 10;
	}

	*pucNibStk++ = (FLMBYTE)uiNum;

	if( bNegFlag)
	{
		*pucNibStk++ = 0x0B;
	}

	f_assert( pucNibStk <= pucNibStkEnd);
	*puiBufLength = ((pucNibStk - ucNibStk) >> 1);

	do
	{
		*pBuf++ = (FLMBYTE)((pucNibStk[ -1] << 4) | pucNibStk[ -2]);
	}
	while( (pucNibStk -= 2) > &ucNibStk[ 1]);

	return( FERR_OK);
}

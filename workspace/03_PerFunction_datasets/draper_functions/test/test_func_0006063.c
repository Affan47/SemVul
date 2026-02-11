copyStr(
	char **			ppszDestStr,
	const char *	pszSrcStr)
{
	RCODE			rc = FERR_OK;
	FLMUINT		uiLen;

	if (pszSrcStr && *pszSrcStr)
	{
		uiLen = f_strlen( pszSrcStr) + 1;
		if (RC_BAD( rc = f_alloc( uiLen, ppszDestStr)))
		{
			goto Exit;
		}
		f_memcpy( *ppszDestStr, pszSrcStr, uiLen);
	}
	else
	{
		*ppszDestStr = NULL;
	}

Exit:

	return( rc);
}

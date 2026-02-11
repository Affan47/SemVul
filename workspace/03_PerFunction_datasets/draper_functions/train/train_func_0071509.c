expImpSeek(
	EXP_IMP_INFO *	pExpImpInfo,
	FLMUINT			uiSeekPos)
{
	RCODE 			rc = FERR_OK;

	if ((uiSeekPos >= pExpImpInfo->ui64FilePos) &&
		 (uiSeekPos < pExpImpInfo->ui64FilePos + (FLMUINT) pExpImpInfo->uiBufUsed))
	{
		pExpImpInfo->uiCurrBuffOffset =
			(FLMUINT) (uiSeekPos - pExpImpInfo->ui64FilePos);
	}
	else
	{
		if (pExpImpInfo->bBufDirty)
		{
			if (RC_BAD( rc = expFlush( pExpImpInfo)))
			{
				goto Exit;
			}
		}

		pExpImpInfo->ui64FilePos = uiSeekPos;
		pExpImpInfo->uiBufUsed = pExpImpInfo->uiCurrBuffOffset = 0;
	}

Exit:

	return (rc);
}

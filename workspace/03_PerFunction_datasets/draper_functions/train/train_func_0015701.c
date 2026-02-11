flmCurDoMatchOp(
	FQATOM *	pLhs,
	FQATOM *	pRhs,
	FLMUINT	uiLang,
	FLMBOOL	bLeadingWildCard,
	FLMBOOL	bTrailingWildCard)
{
	FLMUINT	uiFlags = pLhs->uiFlags | pRhs->uiFlags;
	FLMUINT	uiTrueFalse = 0;


	if (!IS_BUF_TYPE( pLhs->eType) || !IS_BUF_TYPE( pRhs->eType))
	{
		goto Exit;
	}


	if ((pLhs->eType == FLM_BINARY_VAL) || (pRhs->eType == FLM_BINARY_VAL))
	{
		FLMUINT	uiLen1;
		FLMUINT	uiLen2;

		uiLen1 = pLhs->uiBufLen;
		uiLen2 = pRhs->uiBufLen;
		flmAssert( !bLeadingWildCard);
		if ((bTrailingWildCard) && (uiLen2 > uiLen1))
		{
			uiLen2 = uiLen1;
		}

		uiTrueFalse = (FLMUINT)
			(
				(
					(uiLen1 == uiLen2) &&
					(f_memcmp( pLhs->val.pucBuf, pRhs->val.pucBuf, uiLen1) == 0)
				) ? (FLMUINT) FLM_TRUE : (FLMUINT) FLM_FALSE
			);
		goto Exit;
	}


	if (pLhs->eType == FLM_TEXT_VAL && pRhs->eType == FLM_TEXT_VAL)
	{


		uiTrueFalse = flmTextMatch( pLhs->val.pucBuf, pLhs->uiBufLen,
											pRhs->val.pucBuf, pRhs->uiBufLen, uiFlags,
											bLeadingWildCard, bTrailingWildCard, uiLang);
	}
	else
	{
		uiTrueFalse = FLM_FALSE;
	}

Exit:

	return (uiTrueFalse);
}

FSBtResetStack(
	FDB *			pDb,
	LFILE *		pLFile,
	BTSK **		ppStack,
	FLMBYTE *	pElement,
	FLMUINT		elmLen)
{
	RCODE			rc;
	BTSK *		pStack = *ppStack;
	FLMUINT		oldPKC = pStack->uiPKC;
	FLMUINT		oldPvElmPKC = pStack->uiPrevElmPKC;
	FLMUINT		oldBlock = pStack->uiBlkAddr;
	FLMUINT		oldCurElm = pStack->uiCurElm;
	FLMUINT		uiElmOvhd = pStack->uiElmOvhd;

	if (RC_BAD( rc = FSBtSearch( pDb, pLFile, &pStack, &pElement[uiElmOvhd],
				  (elmLen - uiElmOvhd), 0)))
	{
		return (rc);
	}


	while ((oldBlock != pStack->uiBlkAddr) && (oldCurElm != pStack->uiCurElm))
	{
		if ((rc = FSBtNextElm( pDb, pLFile, pStack)) == FERR_BT_END_OF_DATA)
		{
			return (RC_SET( FERR_BTREE_ERROR));
		}
		else if (RC_BAD( rc))
		{
			return (rc);
		}
	}


	pStack->uiPKC = oldPKC;
	pStack->uiPrevElmPKC = oldPvElmPKC;
	*ppStack = pStack;
	pStack->uiFlags = FULL_STACK;

	return (FERR_OK);
}

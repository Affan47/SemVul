scaClearFlags(
	SCACHE *		pSCache,
	FLMUINT16	ui16FlagsToClear)
{
	if( pSCache->ui16Flags)
	{
		if( (pSCache->ui16Flags &= ~ui16FlagsToClear) == 0)
		{
			if( !pSCache->pPrevInGlobalList ||
				pSCache->uiHighTransID == 0xFFFFFFFF ||
				ScaNeededByReadTrans( pSCache->pFile, pSCache))
			{
				ScaLinkToReplaceListAsMRU( pSCache);
			}
			else
			{
				ScaLinkToReplaceListAsLRU( pSCache);
			}
		}
	}
}

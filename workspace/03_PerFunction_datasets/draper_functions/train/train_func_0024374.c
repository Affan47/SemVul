canRelocate(
	void *		pvAlloc)
{
	SCACHE *		pSCache = getSCachePtr( pvAlloc);

	if( !pSCache || pSCache->uiUseCount)
	{
		return( FALSE);
	}

	return( TRUE);
}

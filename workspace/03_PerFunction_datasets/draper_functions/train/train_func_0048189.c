flmRcaAllocCacheStruct(
	RCACHE **		ppRCache)
{
	RCODE				rc = FERR_OK;

	f_assertMutexLocked( gv_FlmSysData.RCacheMgr.hMutex);

	if( (*ppRCache =
		(RCACHE *)gv_FlmSysData.RCacheMgr.pRCacheAlloc->allocCell(
		NULL, NULL)) == NULL)
	{
		rc = RC_SET( FERR_MEM);
		goto Exit;
	}

	f_memset( *ppRCache, 0, sizeof( RCACHE));


	gv_FlmSysData.RCacheMgr.Usage.uiCount++;


	(*ppRCache)->uiHighTransId = 0xFFFFFFFF;

Exit:

	return( rc);
}

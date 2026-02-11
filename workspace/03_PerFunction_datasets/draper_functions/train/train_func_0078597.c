ScaInit(
	FLMUINT					uiMaxSharedCache)
{
	RCODE						rc = FERR_OK;
	FLMUINT					uiLoop;
	FLMUINT					uiBlockSize;
	F_SCacheRelocator *	pSCacheRelocator = NULL;
	F_BlockRelocator *	pBlockRelocator = NULL;

	f_memset( &gv_FlmSysData.SCacheMgr, 0, sizeof( SCACHE_MGR));
	gv_FlmSysData.SCacheMgr.Usage.uiMaxBytes = uiMaxSharedCache;


	if (RC_BAD( rc = ScaInitHashTbl( ScaNumHashBuckets( uiMaxSharedCache))))
	{
		goto Exit;
	}


	if( (pSCacheRelocator = f_new F_SCacheRelocator) == NULL)
	{
		rc = RC_SET( FERR_MEM);
		goto Exit;
	}


	if( RC_BAD( rc = FlmAllocFixedAllocator(
		&gv_FlmSysData.SCacheMgr.pSCacheAllocator)))
	{
		goto Exit;
	}

	if( RC_BAD( rc = gv_FlmSysData.SCacheMgr.pSCacheAllocator->setup(
		FALSE, gv_FlmSysData.pSlabManager, pSCacheRelocator, sizeof( SCACHE),
		&gv_FlmSysData.SCacheMgr.Usage.SlabUsage,
		&gv_FlmSysData.SCacheMgr.Usage.uiTotalBytesAllocated)))
	{
		goto Exit;
	}


	for( uiLoop = 0, uiBlockSize = 4096;
		  uiLoop < 2;
		  uiLoop++, uiBlockSize *= 2)
	{
		if( RC_BAD( rc = FlmAllocBlockAllocator(
			&gv_FlmSysData.SCacheMgr.pBlockAllocators[ uiLoop])))
		{
			goto Exit;
		}

		if( (pBlockRelocator = f_new F_BlockRelocator( uiBlockSize)) == NULL)
		{
			rc = RC_SET( FERR_MEM);
			goto Exit;
		}

		if( RC_BAD( rc = gv_FlmSysData.SCacheMgr.pBlockAllocators[ uiLoop]->setup(
			FALSE, gv_FlmSysData.pSlabManager, pBlockRelocator, uiBlockSize,
			&gv_FlmSysData.SCacheMgr.Usage.SlabUsage,
			&gv_FlmSysData.SCacheMgr.Usage.uiTotalBytesAllocated)))
		{
			goto Exit;
		}

		pBlockRelocator->Release();
		pBlockRelocator = NULL;
	}

Exit:

	if( pSCacheRelocator)
	{
		pSCacheRelocator->Release();
	}

	if( pBlockRelocator)
	{
		pBlockRelocator->Release();
	}

	return( rc);
}

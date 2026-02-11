flmRcaFindRec(
	FFILE *			pFile,
	F_SEM				hWaitSem,
	FLMUINT			uiContainer,
	FLMUINT			uiDrn,
	FLMUINT			uiVersionNeeded,
	FLMBOOL			bDontPoisonCache,
	FLMUINT *		puiNumLooks,
	RCACHE **		ppRCache,
	RCACHE **		ppNewerRCache,
	RCACHE **		ppOlderRCache)
{
	RCACHE *			pRCache;
	FLMUINT			uiNumLooks = 0;
	FLMBOOL			bFound;
	RCACHE *			pNewerRCache;
	RCACHE *			pOlderRCache;


Start_Find:


	pRCache = *(FLM_RCA_HASH( uiDrn));
	bFound = FALSE;
	uiNumLooks = 1;
	while ((pRCache) &&
			 ((pRCache->uiDrn != uiDrn) ||
			  (pRCache->uiContainer != uiContainer) ||
			  (pRCache->pFile != pFile)))
	{
		if ((pRCache = pRCache->pNextInBucket) != NULL)
		{
			uiNumLooks++;
		}
	}


	if (!pRCache)
	{
		pNewerRCache = pOlderRCache = NULL;
	}
	else
	{
		pNewerRCache = NULL;
		pOlderRCache = pRCache;

		for (;;)
		{


			if (RCA_IS_READING_IN( pRCache->uiFlags))
			{


				gv_FlmSysData.RCacheMgr.uiIoWaits++;
				if( RC_BAD( f_notifyWait( gv_FlmSysData.RCacheMgr.hMutex,
					hWaitSem, NULL, &pRCache->pNotifyList)))
				{


					goto Start_Find;
				}


				RCA_DECR_USE_COUNT( pRCache->uiFlags);

				if (RCA_IS_PURGED( pRCache->uiFlags))
				{
					if (!RCA_IS_IN_USE( pRCache->uiFlags))
					{
						flmRcaFreePurged( pRCache);
					}
				}


				goto Start_Find;
			}


			if (uiVersionNeeded < pRCache->uiLowTransId)
			{
				pNewerRCache = pRCache;
				if ((pOlderRCache = pRCache = pRCache->pOlderVersion) == NULL)
				{
					break;
				}
				uiNumLooks++;
			}
			else if (uiVersionNeeded <= pRCache->uiHighTransId)
			{


				if (puiNumLooks)
				{
					if (bDontPoisonCache)
					{
						flmRcaStepUpInGlobalList( pRCache);
					}
					else if (pRCache->pPrevInGlobal)
					{
						flmRcaUnlinkFromGlobal( pRCache);
						flmRcaLinkToGlobalAsMRU( pRCache);
					}

					gv_FlmSysData.RCacheMgr.Usage.uiCacheHits++;
					gv_FlmSysData.RCacheMgr.Usage.uiCacheHitLooks += uiNumLooks;
				}

				bFound = TRUE;
				break;
			}
			else
			{
				pOlderRCache = pRCache;
				pNewerRCache = pRCache->pNewerVersion;


				pRCache = NULL;
				break;
			}
		}
	}

	*ppRCache = pRCache;
	*ppOlderRCache = pOlderRCache;
	*ppNewerRCache = pNewerRCache;

	if (puiNumLooks)
	{
		*puiNumLooks = uiNumLooks;
	}
}

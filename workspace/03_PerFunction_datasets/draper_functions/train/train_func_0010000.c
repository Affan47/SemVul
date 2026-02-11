flmRcaRemoveContainerRecs(
	FDB *			pDb,
	FLMUINT		uiContainer)
{
	FFILE *		pFile = pDb->pFile;
	RCACHE *		pRCache;
	RCACHE *		pPrevRCache;
	FLMUINT		uiTransId = pDb->LogHdr.uiCurrTransID;

	f_mutexLock( gv_FlmSysData.RCacheMgr.hMutex);
	pRCache = gv_FlmSysData.RCacheMgr.pLRURecord;


	while (pRCache)
	{


		pPrevRCache = pRCache->pPrevInGlobal;


		if ((pRCache->uiContainer == uiContainer)  &&
			 (pRCache->pFile == pFile))
		{


			if (pRCache->uiHighTransId == 0xFFFFFFFF)
			{


				flmAssert( pRCache->pNewerVersion == NULL);

				if (pRCache->uiLowTransId < uiTransId)
				{


					flmRcaSetTransID( pRCache, uiTransId - 1);
					flmAssert( pRCache->uiHighTransId >= pRCache->uiLowTransId);
					RCA_SET_UNCOMMITTED( pRCache->uiFlags);
					RCA_SET_LATEST_VER( pRCache->uiFlags);
					flmRcaUnlinkFromFile( pRCache);
					flmRcaLinkToFileAtHead( pRCache, pFile);
				}
				else
				{


					flmRcaFreeCache( pRCache,
								(FLMBOOL)(RCA_IS_IN_USE( pRCache->uiFlags)
											 ? TRUE
											 : FALSE));
				}
			}
			else
			{


				flmAssert( pRCache->uiHighTransId < uiTransId);
			}
		}
		pRCache = pPrevRCache;

	}

	f_mutexUnlock( gv_FlmSysData.RCacheMgr.hMutex);
}

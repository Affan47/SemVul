ScaSavePrevBlkAddress(
	SCACHE *		pSCache)
{
	FLMUINT		uiPrevBlkAddress = scaGetPriorImageAddress( pSCache);
	SCACHE *		pNewerSCache;
	FLMUINT		uiNewerBlkPrevAddress;
	FLMUINT		uiPrevTransID;
	FLMBYTE *	pucTmp;


	if ((uiPrevBlkAddress) &&
		 (uiPrevBlkAddress != BT_END) &&
		 ((pNewerSCache = pSCache->pPrevInVersionList) != NULL) &&
		 (!(pNewerSCache->ui16Flags & CA_READ_PENDING)))
	{


		uiNewerBlkPrevAddress = scaGetPriorImageAddress( pNewerSCache);
		if ((!uiNewerBlkPrevAddress) || (uiNewerBlkPrevAddress == BT_END))
		{


			ScaUseForThread( pNewerSCache, NULL);

			pucTmp = &pNewerSCache->pucBlk [BH_PREV_BLK_ADDR];
			UD2FBA( (FLMUINT32)uiPrevBlkAddress, pucTmp);

			pucTmp = &pNewerSCache->pucBlk [BH_PREV_TRANS_ID];
			uiPrevTransID = scaGetPriorImageTransID( pSCache);
			UD2FBA( (FLMUINT32)uiPrevTransID, pucTmp);


			if( pNewerSCache->ui16Flags & CA_IN_FILE_LOG_LIST)
			{
				ScaUnlinkFromFileLogList( pNewerSCache);
			}

			ScaReleaseForThread( pNewerSCache);
		}
	}
}

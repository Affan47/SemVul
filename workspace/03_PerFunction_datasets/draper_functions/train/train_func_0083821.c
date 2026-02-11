FLRReadBlkHdr(
	FDB *				pDb,
	FLMUINT			uiBlkAddress,
	FLMBYTE *		pucBlockHeader,
	FLMINT *			piTypeRV)
{
	RCODE				rc = FERR_OK;
	FLMUINT			uiBytesRead;
	FLMUINT			uiNumLooks;
	SCACHE *			pBlkSCache;
	DB_STATS *		pDbStats = pDb->pDbStats;
	LFILE_STATS *	pLFileStats;
	F_TMSTAMP		StartTime;
	FLMUINT64		ui64ElapTime;


	if( RC_BAD( rc = ScaGetBlock( pDb, NULL, BHT_LEAF,
		uiBlkAddress, &uiNumLooks, &pBlkSCache)))
	{
		goto Exit;
	}

	if( pBlkSCache)
	{
		f_memcpy( pucBlockHeader, pBlkSCache->pucBlk, BH_OVHD);
		ScaReleaseCache( pBlkSCache, FALSE);
	}
	else
	{
		if( pDbStats)
		{
			ui64ElapTime = 0;
			f_timeGetTimeStamp( &StartTime);
		}

		rc = pDb->pSFileHdl->readBlock( uiBlkAddress,
			pDb->pFile->FileHdr.uiBlockSize,
			pucBlockHeader, &uiBytesRead);

		if( pDbStats)
		{
			flmAddElapTime( &StartTime, &ui64ElapTime);

			if( RC_BAD( rc))
			{
				pDbStats->bHaveStats = TRUE;
				pDbStats->uiReadErrors++;
			}
			else
			{
				FLMUINT				uiLFileNum;
				BLOCKIO_STATS *	pBlockIOStats;
				FLMUINT				uiBlkType;

				uiLFileNum = FB2UW( &pucBlockHeader [BH_LOG_FILE_NUM]);
				if( !uiLFileNum)
				{
					pLFileStats = NULL;
					uiBlkType = (FLMUINT)BH_GET_TYPE( pucBlockHeader);
				}
				else
				{
					FLMBYTE	ucLfType = 0xFF;
					LFILE *	pTmpLFile;

					if( uiLFileNum == FLM_DICT_INDEX ||
						RC_OK( fdictGetIndex(
							pDb->pDict, pDb->pFile->bInLimitedMode,
							uiLFileNum, NULL, NULL, TRUE)))
					{
						ucLfType = LF_INDEX;
					}
					else if( RC_OK( fdictGetContainer( pDb->pDict, uiLFileNum, &pTmpLFile)))
					{
						ucLfType = LF_CONTAINER;
					}

					if( RC_BAD( flmStatGetLFile( pDbStats,
													uiLFileNum, ucLfType, 0,
													&pLFileStats, NULL, NULL)))
					{
						pLFileStats = NULL;
					}
					if (pLFileStats)
						uiBlkType = BHT_LEAF;
					else
						uiBlkType = (FLMUINT)BH_GET_TYPE( pucBlockHeader);
				}
				if ((pBlockIOStats = flmGetBlockIOStatPtr( pDbStats,
												pLFileStats, pucBlockHeader,
												uiBlkType)) != NULL)
				{
					pDbStats->bHaveStats = TRUE;
					if (pLFileStats)
					{
						pLFileStats->bHaveStats = TRUE;
					}
					pBlockIOStats->BlockReads.ui64ElapMilli += ui64ElapTime;
					pBlockIOStats->BlockReads.ui64Count++;
					pBlockIOStats->BlockReads.ui64TotalBytes += BH_OVHD;
				}
			}
		}

		if( RC_BAD( rc))
		{
			goto Exit;
		}

		pucBlockHeader [BH_CHECKSUM_LOW] = (FLMBYTE) uiBlkAddress;
	}


	if (piTypeRV)
	{
		*piTypeRV = BH_GET_TYPE( pucBlockHeader );
	}

Exit:

	return( rc);
}

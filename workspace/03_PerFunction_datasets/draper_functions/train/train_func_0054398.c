chkReportError(
	DB_INFO *			pDbInfo,
	eCorruptionType	eCorruption,
	eCorruptionLocale eErrLocale,
	FLMUINT				uiErrLfNumber,
	FLMUINT				uiErrLfType,
	FLMUINT				uiErrBTreeLevel,
	FLMUINT				uiErrBlkAddress,
	FLMUINT				uiErrParentBlkAddress,
	FLMUINT				uiErrElmOffset,
	FLMUINT				uiErrDrn,
	FLMUINT				uiErrElmRecOffset,
	FLMUINT				uiErrFieldNum,
	FLMBYTE *			pBlk)
{
	CORRUPT_INFO	CorruptInfo;
	FLMBOOL			bFixErr;

	CorruptInfo.eCorruption = eCorruption;
	CorruptInfo.eErrLocale = eErrLocale;
	CorruptInfo.uiErrLfNumber = uiErrLfNumber;
	CorruptInfo.uiErrLfType = uiErrLfType;
	CorruptInfo.uiErrBTreeLevel = uiErrBTreeLevel;
	CorruptInfo.uiErrBlkAddress = uiErrBlkAddress;
	CorruptInfo.uiErrParentBlkAddress = uiErrParentBlkAddress;
	CorruptInfo.uiErrElmOffset = uiErrElmOffset;
	CorruptInfo.uiErrDrn = uiErrDrn;
	CorruptInfo.uiErrElmRecOffset = uiErrElmRecOffset;
	CorruptInfo.uiErrFieldNum = uiErrFieldNum;
	CorruptInfo.pBlk = pBlk;
	CorruptInfo.pErrIxKey = NULL;
	CorruptInfo.pErrRecord = NULL;
	CorruptInfo.pErrRecordKeyList = NULL;
	if ((pDbInfo->fnStatusFunc) && (RC_OK( pDbInfo->LastStatusRc)))
	{
		bFixErr = FALSE;
		pDbInfo->LastStatusRc = (*pDbInfo->fnStatusFunc)
			(FLM_PROBLEM_STATUS, (void *) &CorruptInfo, (void *) &bFixErr,
			pDbInfo->pProgress->AppArg);
	}

	if (eCorruption != FLM_OLD_VIEW)
	{
		pDbInfo->pProgress->bPhysicalCorrupt = TRUE;
		pDbInfo->uiFlags &= ~FLM_CHK_INDEX_REFERENCING;
	}

	return (pDbInfo->LastStatusRc);
}

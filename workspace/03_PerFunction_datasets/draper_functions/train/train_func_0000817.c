flmBackgroundIndexGet(
	FFILE *			pFile,
	FLMUINT			uiIndexNum,
	FLMBOOL			bMutexLocked,
	FLMUINT *		puiThreadId)
{
	RCODE				rc = FERR_OK;
	IF_Thread *		pThread;
	FLMUINT			uiThreadId;
	F_BKGND_IX *	pBackgroundIx = NULL;

	if( !bMutexLocked)
	{
		f_mutexLock( gv_FlmSysData.hShareMutex);
	}

	uiThreadId = 0;
	for( ;;)
	{
		if( RC_BAD( rc = gv_FlmSysData.pThreadMgr->getNextGroupThread(
			&pThread, gv_uiBackIxThrdGroup, &uiThreadId)))
		{
			if( rc == FERR_NOT_FOUND)
			{
				rc = FERR_OK;
				break;
			}
			else
			{
				flmAssert( 0);
			}
		}

		if( pThread->getThreadAppId())
		{
			F_BKGND_IX *		pTmpIx = NULL;

			pTmpIx = (F_BKGND_IX *)pThread->getParm1();
			if( pTmpIx->indexStatus.uiIndexNum == uiIndexNum &&
				pTmpIx->pFile == pFile)
			{
				flmAssert( pThread->getThreadAppId() == uiIndexNum);
				pBackgroundIx = pTmpIx;
				pThread->Release();
				if( puiThreadId)
				{
					*puiThreadId = uiThreadId;
				}
				break;
			}
		}
		pThread->Release();
	}

	if( !bMutexLocked)
	{
		f_mutexUnlock( gv_FlmSysData.hShareMutex);
	}

	return( pBackgroundIx);
}

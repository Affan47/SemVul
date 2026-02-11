flmStatStop(
	FLM_STATS *	pStats
	)
{


	if (pStats->hMutex != F_MUTEX_NULL)
	{
		f_mutexLock( pStats->hMutex);
	}

	if (pStats->bCollectingStats)
	{
		pStats->bCollectingStats = FALSE;
		f_timeGetSeconds( &pStats->uiStopTime);
	}


	if (pStats->hMutex != F_MUTEX_NULL)
	{
		f_mutexUnlock( pStats->hMutex);
	}
}

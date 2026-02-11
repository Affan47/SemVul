FSFreeIxCounts(
	FDB *			pDb)
{
	IX_STATS *	pNextIxStat;

	while (pDb->pIxStats)
	{
		pNextIxStat = pDb->pIxStats->pNext;
		f_free( &pDb->pIxStats);
		pDb->pIxStats = pNextIxStat;
	}
}

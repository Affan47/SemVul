printOperationStats(
	STAT_GATHER *		pStatGather,
	STAT_GATHER *		pOldStatGather)
{
	F_COUNT_TIME_STAT	Stat;
	F_COUNT_TIME_STAT	OldStat;
	FLMBOOL				bHighlight;

	if (pStatGather->uiStartTime)
	{
		fnPrintf( m_pHRequest, "<br>\n");


		printTableStart( "Database Operations", 4, 75);


		printTableRowStart();
		printColumnHeading( "Operation", JUSTIFY_LEFT);
		printColumnHeading( "Count", JUSTIFY_RIGHT);
		printColumnHeading( "Total Seconds", JUSTIFY_RIGHT);
		printColumnHeading( "Avg Seconds", JUSTIFY_RIGHT);
		printTableRowEnd();


		bHighlight = FALSE;
		printCountTimeRow( bHighlight = ~bHighlight, "Committed Update Trans",
			&pStatGather->CommittedUpdTrans,
			&pOldStatGather->CommittedUpdTrans);
		printCountTimeRow( bHighlight = ~bHighlight, "Aborted Update Trans",
			&pStatGather->AbortedUpdTrans,
			&pOldStatGather->AbortedUpdTrans);
		printCountTimeRow( bHighlight = ~bHighlight, "Group Finishes",
			&pStatGather->GroupCompletes,
			&pOldStatGather->GroupCompletes);

		Stat.ui64Count = pStatGather->ui64GroupFinished;
		OldStat.ui64Count = pOldStatGather->ui64GroupFinished;
		printCountTimeRow( bHighlight = ~bHighlight, "Total Finished",
			&Stat, &OldStat, TRUE);

		if (pStatGather->GroupCompletes.ui64Count)
		{
			Stat.ui64Count = pStatGather->ui64GroupFinished /
				pStatGather->GroupCompletes.ui64Count;
		}
		else
		{
			Stat.ui64Count = 0;
		}
		if (pOldStatGather->GroupCompletes.ui64Count)
		{
			OldStat.ui64Count = pOldStatGather->ui64GroupFinished /
				pOldStatGather->GroupCompletes.ui64Count;
		}
		else
		{
			OldStat.ui64Count = 0;
		}
		printCountTimeRow( bHighlight = ~bHighlight, "Average Per Group",
			&Stat, &OldStat, TRUE);

		printCountTimeRow( bHighlight = ~bHighlight, "Committed Read Trans",
			&pStatGather->CommittedReadTrans,
			&pOldStatGather->CommittedReadTrans);
		printCountTimeRow( bHighlight = ~bHighlight, "Aborted Read Trans",
			&pStatGather->AbortedReadTrans,
			&pOldStatGather->AbortedReadTrans);
		printCountTimeRow( bHighlight = ~bHighlight, "Reads",
			&pStatGather->Reads,
			&pOldStatGather->Reads);
		printCountTimeRow( bHighlight = ~bHighlight, "Adds",
			&pStatGather->Adds,
			&pOldStatGather->Adds);
		printCountTimeRow( bHighlight = ~bHighlight, "Modifies",
			&pStatGather->Modifies,
			&pOldStatGather->Modifies);
		printCountTimeRow( bHighlight = ~bHighlight, "Deletes",
			&pStatGather->Deletes,
			&pOldStatGather->Deletes);
		printCountTimeRow( bHighlight = ~bHighlight, "Queries",
			&pStatGather->Queries,
			&pOldStatGather->Queries, TRUE);
		printCountTimeRow( bHighlight = ~bHighlight, "Query Reads",
			&pStatGather->QueryReads,
			&pOldStatGather->QueryReads, TRUE);

		Stat.ui64Count = pStatGather->ui64BlockSplits;
		OldStat.ui64Count = pOldStatGather->ui64BlockSplits;
		printCountTimeRow( bHighlight = ~bHighlight, "Block Splits",
			&Stat, &OldStat, TRUE);

		Stat.ui64Count = pStatGather->ui64BlockCombines;
		OldStat.ui64Count = pOldStatGather->ui64BlockCombines;
		printCountTimeRow( bHighlight = ~bHighlight, "Block Combines",
			&Stat, &OldStat, TRUE);

		printTableEnd();
	}
}

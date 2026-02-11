lazy_vacuum_rel(Relation onerel, VacuumStmt *vacstmt)
{
	LVRelStats *vacrelstats;
	Relation   *Irel;
	int			nindexes;
	BlockNumber possibly_freeable;
	bool		heldoff = false;

	if (vacstmt->verbose)
		elevel = INFO;
	else
		elevel = DEBUG2;

	vacuum_set_xid_limits(vacstmt, onerel->rd_rel->relisshared,
						  &OldestXmin, &FreezeLimit);

	vacrelstats = (LVRelStats *) palloc0(sizeof(LVRelStats));


	vacrelstats->threshold = GetAvgFSMRequestSize(&onerel->rd_node);


	vac_open_indexes(onerel, RowExclusiveLock, &nindexes, &Irel);
	vacrelstats->hasindex = (nindexes > 0);


	lazy_scan_heap(onerel, vacrelstats, Irel, nindexes);


	vac_close_indexes(nindexes, Irel, NoLock);


	possibly_freeable = vacrelstats->rel_pages - vacrelstats->nonempty_pages;
	if (possibly_freeable > 0 &&
		(possibly_freeable >= REL_TRUNCATE_MINIMUM ||
		 possibly_freeable >= vacrelstats->rel_pages / REL_TRUNCATE_FRACTION))
	{
		HOLD_INTERRUPTS();
		heldoff = true;
		lazy_truncate_heap(onerel, vacrelstats);
	}


	lazy_update_fsm(onerel, vacrelstats);


	vac_update_relstats(RelationGetRelid(onerel),
						vacrelstats->rel_pages,
						vacrelstats->rel_tuples,
						vacrelstats->hasindex,
						FreezeLimit);


	pgstat_report_vacuum(RelationGetRelid(onerel), onerel->rd_rel->relisshared,
						 vacstmt->analyze, vacrelstats->rel_tuples);

	return heldoff;
}

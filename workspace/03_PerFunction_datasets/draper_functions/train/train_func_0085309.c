lazy_vacuum_index(Relation indrel,
				  IndexBulkDeleteResult **stats,
				  LVRelStats *vacrelstats)
{
	IndexVacuumInfo ivinfo;
	PGRUsage	ru0;

	pg_rusage_init(&ru0);

	ivinfo.index = indrel;
	ivinfo.vacuum_full = false;
	ivinfo.analyze_only = false;
	ivinfo.estimated_count = true;
	ivinfo.message_level = elevel;
	ivinfo.num_heap_tuples = vacrelstats->old_rel_tuples;
	ivinfo.strategy = vac_strategy;


	*stats = index_bulk_delete(&ivinfo, *stats,
							   lazy_tid_reaped, (void *) vacrelstats);

	ereport(elevel,
			(errmsg("scanned index \"%s\" to remove %d row versions",
					RelationGetRelationName(indrel),
					vacrelstats->num_dead_tuples),
			 errdetail("%s.", pg_rusage_show(&ru0))));
}

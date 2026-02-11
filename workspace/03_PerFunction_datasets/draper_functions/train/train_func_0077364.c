lazy_cleanup_index(Relation indrel,
				   IndexBulkDeleteResult *stats,
				   LVRelStats *vacrelstats)
{
	IndexVacuumInfo ivinfo;
	PGRUsage	ru0;

	pg_rusage_init(&ru0);

	ivinfo.index = indrel;
	ivinfo.analyze_only = false;
	ivinfo.estimated_count = (vacrelstats->scanned_pages < vacrelstats->rel_pages);
	ivinfo.message_level = elevel;
	ivinfo.num_heap_tuples = vacrelstats->new_rel_tuples;
	ivinfo.strategy = vac_strategy;

	stats = index_vacuum_cleanup(&ivinfo, stats);

	if (!stats)
		return;


	if (!stats->estimated_count)
		vac_update_relstats(indrel,
							stats->num_pages, stats->num_index_tuples,
							false, InvalidTransactionId);

	ereport(elevel,
			(errmsg("index \"%s\" now contains %.0f row versions in %u pages",
					RelationGetRelationName(indrel),
					stats->num_index_tuples,
					stats->num_pages),
			 errdetail("%.0f index row versions were removed.\n"
			 "%u index pages have been deleted, %u are currently reusable.\n"
					   "%s.",
					   stats->tuples_removed,
					   stats->pages_deleted, stats->pages_free,
					   pg_rusage_show(&ru0))));

	pfree(stats);
}

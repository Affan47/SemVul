autovac_init(void)
{
	if (!autovacuum_start_daemon)
		return;

	if (!pgstat_collect_startcollector || !pgstat_collect_tuplelevel)
	{
		ereport(WARNING,
				(errmsg("autovacuum not started because of misconfiguration"),
				 errhint("Enable options \"stats_start_collector\" and \"stats_row_level\".")));


		autovacuum_start_daemon = false;
	}
}

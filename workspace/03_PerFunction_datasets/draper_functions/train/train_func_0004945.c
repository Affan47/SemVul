autovac_init(void)
{
	if (autovacuum_start_daemon && !pgstat_track_counts)
		ereport(WARNING,
				(errmsg("autovacuum not started because of misconfiguration"),
				 errhint("Enable the \"track_counts\" option.")));
}

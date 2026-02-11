pgstat_report_xact_timestamp(TimestampTz tstamp)
{
	volatile PgBackendStatus *beentry = MyBEEntry;

	if (!pgstat_track_activities || !beentry)
		return;


	beentry->st_changecount++;
	beentry->st_xact_start_timestamp = tstamp;
	beentry->st_changecount++;
	Assert((beentry->st_changecount & 1) == 0);
}

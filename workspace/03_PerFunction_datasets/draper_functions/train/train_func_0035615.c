pgstat_read_current_status(void)
{
	volatile PgBackendStatus *beentry;
	PgBackendStatus *localtable;
	PgBackendStatus *localentry;
	char	   *localactivity;
	int			i;

	Assert(!pgStatRunningInCollector);
	if (localBackendStatusTable)
		return;

	pgstat_setup_memcxt();

	localtable = (PgBackendStatus *)
		MemoryContextAlloc(pgStatLocalContext,
						   sizeof(PgBackendStatus) * MaxBackends);
	localactivity = (char *)
		MemoryContextAlloc(pgStatLocalContext,
						   pgstat_track_activity_query_size * MaxBackends);
	localNumBackends = 0;

	beentry = BackendStatusArray;
	localentry = localtable;
	for (i = 1; i <= MaxBackends; i++)
	{


		for (;;)
		{
			int			save_changecount = beentry->st_changecount;

			localentry->st_procpid = beentry->st_procpid;
			if (localentry->st_procpid > 0)
			{
				memcpy(localentry, (char *) beentry, sizeof(PgBackendStatus));


				strcpy(localactivity, (char *) beentry->st_activity);
				localentry->st_activity = localactivity;
			}

			if (save_changecount == beentry->st_changecount &&
				(save_changecount & 1) == 0)
				break;


			CHECK_FOR_INTERRUPTS();
		}

		beentry++;

		if (localentry->st_procpid > 0)
		{
			localentry++;
			localactivity += pgstat_track_activity_query_size;
			localNumBackends++;
		}
	}


	localBackendStatusTable = localtable;
}

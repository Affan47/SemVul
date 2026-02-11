pgstat_bestart(void)
{
	volatile PgBackendStatus *beentry;
	TimestampTz proc_start_timestamp;
	Oid			userid;
	SockAddr	clientaddr;

	Assert(MyBackendId >= 1 && MyBackendId <= MaxBackends);
	MyBEEntry = &BackendStatusArray[MyBackendId - 1];


	if (MyProcPort)
		proc_start_timestamp = MyProcPort->SessionStartTime;
	else
		proc_start_timestamp = GetCurrentTimestamp();
	userid = GetSessionUserId();


	if (MyProcPort)
		memcpy(&clientaddr, &MyProcPort->raddr, sizeof(clientaddr));
	else
		MemSet(&clientaddr, 0, sizeof(clientaddr));


	beentry = MyBEEntry;
	do
	{
		beentry->st_changecount++;
	} while ((beentry->st_changecount & 1) == 0);

	beentry->st_procpid = MyProcPid;
	beentry->st_proc_start_timestamp = proc_start_timestamp;
	beentry->st_activity_start_timestamp = 0;
	beentry->st_databaseid = MyDatabaseId;
	beentry->st_userid = userid;
	beentry->st_clientaddr = clientaddr;
	beentry->st_waiting = false;
	beentry->st_activity[0] = '\0';

	beentry->st_activity[PGBE_ACTIVITY_SIZE - 1] = '\0';

	beentry->st_changecount++;
	Assert((beentry->st_changecount & 1) == 0);


	on_shmem_exit(pgstat_beshutdown_hook, 0);
}

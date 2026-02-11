ServerLoop(void)
{
	fd_set		readmask;
	int			nSockets;
	time_t		now,
				last_touch_time;

	last_touch_time = time(NULL);

	nSockets = initMasks(&readmask);

	for (;;)
	{
		fd_set		rmask;
		int			selres;


		memcpy((char *) &rmask, (char *) &readmask, sizeof(fd_set));

		PG_SETMASK(&UnBlockSig);

		if (pmState == PM_WAIT_DEAD_END)
		{
			pg_usleep(100000L);
			selres = 0;
		}
		else
		{

			struct timeval timeout;

			timeout.tv_sec = 60;
			timeout.tv_usec = 0;

			selres = select(nSockets, &rmask, NULL, NULL, &timeout);
		}


		PG_SETMASK(&BlockSig);


		if (selres < 0)
		{
			if (errno != EINTR && errno != EWOULDBLOCK)
			{
				ereport(LOG,
						(errcode_for_socket_access(),
						 errmsg("select() failed in postmaster: %m")));
				return STATUS_ERROR;
			}
		}


		if (selres > 0)
		{
			int			i;

			for (i = 0; i < MAXLISTEN; i++)
			{
				if (ListenSocket[i] == -1)
					break;
				if (FD_ISSET(ListenSocket[i], &rmask))
				{
					Port	   *port;

					port = ConnCreate(ListenSocket[i]);
					if (port)
					{
						BackendStartup(port);


						StreamClose(port->sock);
						ConnFree(port);
					}
				}
			}
		}


		if (SysLoggerPID == 0 && Logging_collector)
			SysLoggerPID = SysLogger_Start();


		if (BgWriterPID == 0 &&
			(pmState == PM_RUN || pmState == PM_RECOVERY ||
			 pmState == PM_RECOVERY_CONSISTENT))
			BgWriterPID = StartBackgroundWriter();


		if (WalWriterPID == 0 && pmState == PM_RUN)
			WalWriterPID = StartWalWriter();


		if (AutoVacPID == 0 &&
			(AutoVacuumingActive() || start_autovac_launcher) &&
			pmState == PM_RUN)
		{
			AutoVacPID = StartAutoVacLauncher();
			if (AutoVacPID != 0)
				start_autovac_launcher = false;
		}


		if (XLogArchivingActive() && PgArchPID == 0 && pmState == PM_RUN)
			PgArchPID = pgarch_start();


		if (PgStatPID == 0 && pmState == PM_RUN)
			PgStatPID = pgstat_start();


		if (avlauncher_needs_signal)
		{
			avlauncher_needs_signal = false;
			if (AutoVacPID != 0)
				kill(AutoVacPID, SIGUSR1);
		}


		now = time(NULL);
		if (now - last_touch_time >= 58 * SECS_PER_MINUTE)
		{
			TouchSocketFile();
			TouchSocketLockFile();
			last_touch_time = now;
		}
	}
}

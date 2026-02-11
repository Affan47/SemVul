WaitForBackgroundWorkerStartup(BackgroundWorkerHandle *handle, pid_t *pidp)
{
	BgwHandleStatus status;
	int			rc;
	bool		save_set_latch_on_sigusr1;

	save_set_latch_on_sigusr1 = set_latch_on_sigusr1;
	set_latch_on_sigusr1 = true;

	PG_TRY();
	{
		for (;;)
		{
			pid_t		pid;

			CHECK_FOR_INTERRUPTS();

			status = GetBackgroundWorkerPid(handle, &pid);
			if (status == BGWH_STARTED)
				*pidp = pid;
			if (status != BGWH_NOT_YET_STARTED)
				break;

			rc = WaitLatch(MyLatch,
						   WL_LATCH_SET | WL_POSTMASTER_DEATH, 0);

			if (rc & WL_POSTMASTER_DEATH)
			{
				status = BGWH_POSTMASTER_DIED;
				break;
			}

			ResetLatch(MyLatch);
		}
	}
	PG_CATCH();
	{
		set_latch_on_sigusr1 = save_set_latch_on_sigusr1;
		PG_RE_THROW();
	}
	PG_END_TRY();

	set_latch_on_sigusr1 = save_set_latch_on_sigusr1;
	return status;
}

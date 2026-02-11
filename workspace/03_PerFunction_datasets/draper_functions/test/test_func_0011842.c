RequestCheckpoint(int flags)
{

	volatile BgWriterShmemStruct *bgs = BgWriterShmem;
	int			ntries;
	int			old_failed,
				old_started;


	if (!IsPostmasterEnvironment)
	{


		CreateCheckPoint(flags | CHECKPOINT_IMMEDIATE);


		smgrcloseall();

		return;
	}


	SpinLockAcquire(&bgs->ckpt_lck);

	old_failed = bgs->ckpt_failed;
	old_started = bgs->ckpt_started;
	bgs->ckpt_flags |= flags;

	SpinLockRelease(&bgs->ckpt_lck);


	for (ntries = 0;; ntries++)
	{
		if (BgWriterShmem->bgwriter_pid == 0)
		{
			if (ntries >= 20)
			{
				elog((flags & CHECKPOINT_WAIT) ? ERROR : LOG,
				"could not request checkpoint because bgwriter not running");
				break;
			}
		}
		else if (kill(BgWriterShmem->bgwriter_pid, SIGINT) != 0)
		{
			if (ntries >= 20)
			{
				elog((flags & CHECKPOINT_WAIT) ? ERROR : LOG,
					 "could not signal for checkpoint: %m");
				break;
			}
		}
		else
			break;

		CHECK_FOR_INTERRUPTS();
		pg_usleep(100000L);
	}


	if (flags & CHECKPOINT_WAIT)
	{
		int			new_started,
					new_failed;


		for (;;)
		{
			SpinLockAcquire(&bgs->ckpt_lck);
			new_started = bgs->ckpt_started;
			SpinLockRelease(&bgs->ckpt_lck);

			if (new_started != old_started)
				break;

			CHECK_FOR_INTERRUPTS();
			pg_usleep(100000L);
		}


		for (;;)
		{
			int			new_done;

			SpinLockAcquire(&bgs->ckpt_lck);
			new_done = bgs->ckpt_done;
			new_failed = bgs->ckpt_failed;
			SpinLockRelease(&bgs->ckpt_lck);

			if (new_done - new_started >= 0)
				break;

			CHECK_FOR_INTERRUPTS();
			pg_usleep(100000L);
		}

		if (new_failed != old_failed)
			ereport(ERROR,
					(errmsg("checkpoint request failed"),
					 errhint("Consult recent messages in the server log for details.")));
	}
}

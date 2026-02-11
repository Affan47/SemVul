recoveryPausesHere(void)
{
	ereport(LOG,
			(errmsg("recovery has paused"),
			 errhint("Execute pg_xlog_replay_resume() to continue.")));

	while (RecoveryIsPaused())
	{
		pg_usleep(1000000L);
		HandleStartupProcInterrupts();
	}
}

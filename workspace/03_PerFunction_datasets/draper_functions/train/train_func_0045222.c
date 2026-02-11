SIGHUP_handler(SIGNAL_ARGS)
{
	int			save_errno = errno;

	PG_SETMASK(&BlockSig);

	if (Shutdown <= SmartShutdown)
	{
		ereport(LOG,
				(errmsg("received SIGHUP, reloading configuration files")));
		ProcessConfigFile(PGC_SIGHUP);
		SignalChildren(SIGHUP);
		if (BgWriterPID != 0)
			signal_child(BgWriterPID, SIGHUP);
		if (WalWriterPID != 0)
			signal_child(WalWriterPID, SIGHUP);
		if (AutoVacPID != 0)
			signal_child(AutoVacPID, SIGHUP);
		if (PgArchPID != 0)
			signal_child(PgArchPID, SIGHUP);
		if (SysLoggerPID != 0)
			signal_child(SysLoggerPID, SIGHUP);


		load_hba();
		load_ident();

#ifdef EXEC_BACKEND

		write_nondefault_variables(PGC_SIGHUP);
#endif
	}

	PG_SETMASK(&UnBlockSig);

	errno = save_errno;
}

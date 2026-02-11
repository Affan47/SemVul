StartChildProcess(AuxProcType type)
{
	pid_t		pid;
	char	   *av[10];
	int			ac = 0;
	char		typebuf[32];


	av[ac++] = "postgres";

#ifdef EXEC_BACKEND
	av[ac++] = "--forkboot";
	av[ac++] = NULL;
#endif

	snprintf(typebuf, sizeof(typebuf), "-x%d", type);
	av[ac++] = typebuf;

	av[ac] = NULL;
	Assert(ac < lengthof(av));

#ifdef EXEC_BACKEND
	pid = postmaster_forkexec(ac, av);
#else
	pid = fork_process();

	if (pid == 0)
	{
		IsUnderPostmaster = true;


		ClosePostmasterPorts(false);


		on_exit_reset();


		MemoryContextSwitchTo(TopMemoryContext);
		MemoryContextDelete(PostmasterContext);
		PostmasterContext = NULL;

		AuxiliaryProcessMain(ac, av);
		ExitPostmaster(0);
	}
#endif

	if (pid < 0)
	{

		int			save_errno = errno;

		errno = save_errno;
		switch (type)
		{
			case StartupProcess:
				ereport(LOG,
						(errmsg("could not fork startup process: %m")));
				break;
			case BgWriterProcess:
				ereport(LOG,
				   (errmsg("could not fork background writer process: %m")));
				break;
			case WalWriterProcess:
				ereport(LOG,
						(errmsg("could not fork WAL writer process: %m")));
				break;
			default:
				ereport(LOG,
						(errmsg("could not fork process: %m")));
				break;
		}


		if (type == StartupProcess)
			ExitPostmaster(1);
		return 0;
	}


	return pid;
}

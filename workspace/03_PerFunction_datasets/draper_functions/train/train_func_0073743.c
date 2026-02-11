do_status(void)
{
	pgpid_t		pid;

	pid = get_pgpid();
	if (pid != 0)
	{
		if (pid < 0)
		{
			pid = -pid;
			if (postmaster_is_alive((pid_t) pid))
			{
				printf(_("%s: single-user server is running (PID: %ld)\n"),
					   progname, pid);
				return;
			}
		}
		else

		{
			if (postmaster_is_alive((pid_t) pid))
			{
				char	  **optlines;

				printf(_("%s: server is running (PID: %ld)\n"),
					   progname, pid);

				optlines = readfile(postopts_file);
				if (optlines != NULL)
					for (; *optlines != NULL; optlines++)
						fputs(*optlines, stdout);
				return;
			}
		}
	}
	printf(_("%s: no server running\n"), progname);
	exit(1);
}

sigterm(int n)
{
	if (child_pid > 0)
	{
		hup_restart = 0;
		respawn = 0;
		kill(child_pid, SIGTERM);
		signal(SIGALRM, sigalrm);
		alarm(8);
	}
	else exit(0);
#if	RETSIGTYPE != void
	return (1);
#endif
}

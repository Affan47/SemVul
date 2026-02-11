background(void)
{
	int	pid;

	if ((pid = fork()) < 0)
		fatal_with_errno(EXIT_FAILURE, "Unable to enter background");

	xbit_set(&upslog_flags, UPSLOG_SYSLOG);
	xbit_clear(&upslog_flags, UPSLOG_STDERR);

	close(0);
	close(1);
	close(2);

	if (pid != 0)
		_exit(EXIT_SUCCESS);


	if (open("/dev/null", O_RDWR) != 0)
		fatal_with_errno(EXIT_FAILURE, "open /dev/null");

	if (dup(0) == -1)
		fatal_with_errno(EXIT_FAILURE, "dup");

	if (dup(0) == -1)
		fatal_with_errno(EXIT_FAILURE, "dup");

#ifdef HAVE_SETSID
	setsid();
#endif

	upslogx(LOG_INFO, "Startup successful");
}

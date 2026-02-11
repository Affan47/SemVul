setup_signals(void)
{
	struct	sigaction	sa;

	sigemptyset(&nut_upslog_sigmask);
	sigaddset(&nut_upslog_sigmask, SIGHUP);
	sa.sa_mask = nut_upslog_sigmask;
	sa.sa_handler = set_reopen_flag;
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		fatal_with_errno(EXIT_FAILURE, "Can't install SIGHUP handler");

	sa.sa_handler = set_exit_flag;
	if (sigaction(SIGINT, &sa, NULL) < 0)
		fatal_with_errno(EXIT_FAILURE, "Can't install SIGINT handler");
	if (sigaction(SIGQUIT, &sa, NULL) < 0)
		fatal_with_errno(EXIT_FAILURE, "Can't install SIGQUIT handler");
	if (sigaction(SIGTERM, &sa, NULL) < 0)
		fatal_with_errno(EXIT_FAILURE, "Can't install SIGTERM handler");
}

commonsetup() {

	struct sigaction sa_chld;
#ifndef DISABLE_SYSLOG
	if (svr_opts.usingsyslog) {
		startsyslog();
	}
#endif


	if (signal(SIGINT, sigintterm_handler) == SIG_ERR ||
#ifndef DEBUG_VALGRIND
		signal(SIGTERM, sigintterm_handler) == SIG_ERR ||
#endif
		signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
		dropbear_exit("signal() error");
	}


	sa_chld.sa_handler = sigchld_handler;
	sa_chld.sa_flags = SA_NOCLDSTOP;
	if (sigaction(SIGCHLD, &sa_chld, NULL) < 0) {
		dropbear_exit("signal() error");
	}
	if (signal(SIGSEGV, sigsegv_handler) == SIG_ERR) {
		dropbear_exit("signal() error");
	}


	loadhostkeys();

    seedrandom();
}

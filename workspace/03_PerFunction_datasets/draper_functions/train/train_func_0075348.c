init_sighandlers(void)
{
	sigset_t sigs;
	struct sigaction action;


	sigemptyset(&sigs);
	pthread_sigmask(SIG_SETMASK, &sigs, NULL);

	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	action.sa_handler = sigterm_handler;


	if (sigaction(SIGTERM, &action, NULL) < 0) {
		message_strerr(LOG_ERR, errno,
			"unable to install signal handler for SIGTERM");
		die(EXIT_OSERR);
	}
	if (sigaction(SIGINT, &action, NULL) < 0) {
	        message_strerr(LOG_ERR, errno,
			"unable to install signal handler for SIGINT");
	        die(EXIT_OSERR);
	}


	action.sa_flags = SA_RESTART;
	action.sa_handler = sigusr1_handler;
	if (sigaction(SIGUSR1, &action, NULL) < 0) {
	        message_strerr(LOG_ERR, errno,
			"unable to install signal handler for SIGUSR1");
	        die(EXIT_OSERR);
	}

	gotsigterm = gotsigusr1 = 0;
	sigemptyset(&sigs);
	sigaddset(&sigs, SIGTERM);
	sigaddset(&sigs, SIGINT);
	sigaddset(&sigs, SIGUSR1);
	pthread_sigmask(SIG_UNBLOCK, &sigs, NULL);
}

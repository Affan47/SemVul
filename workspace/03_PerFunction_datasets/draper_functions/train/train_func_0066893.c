signals_add_handlers(int alarm)
{
    struct sigaction action;
    int i;

    sigemptyset(&action.sa_mask);

    action.sa_flags = 0;
#ifdef SA_RESETHAND
    action.sa_flags |= SA_RESETHAND;
#endif

    action.sa_handler = sighandler;


    if (alarm && sigaction(SIGALRM, &action, NULL) < 0) {
	fatal("unable to install signal handler for %d: %m", SIGALRM);
    }


    if (sigaction(SIGQUIT, &action, NULL) < 0) {
	fatal("unable to install signal handler for %d: %m", SIGQUIT);
    }

#ifdef SA_RESTART
    action.sa_flags |= SA_RESTART;
#endif

    for (i = 0; catch[i] != 0; i++) {
	if (catch[i] != SIGALRM && sigaction(catch[i], &action, NULL) < 0) {
	    fatal("unable to install signal handler for %d: %m", catch[i]);
	}
    }
}

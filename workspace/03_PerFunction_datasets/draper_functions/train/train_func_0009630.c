setsigalrm(int enable)

{
    struct sigaction action;

    sigemptyset(&action.sa_mask);

    action.sa_flags = 0;

    if(enable) {
	action.sa_handler = cyrus_timeout;
    } else {
	action.sa_handler = SIG_IGN;
    }

    if (sigaction(SIGALRM, &action, NULL) < 0) {
	syslog(LOG_ERR, "installing SIGALRM handler: sigaction: %m");
	return -1;
    }

    return 0;
}

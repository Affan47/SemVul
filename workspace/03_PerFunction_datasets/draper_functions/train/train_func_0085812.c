sig_handlers(void)
{
#ifndef _MSC_VER

	struct sigaction action;


	action.sa_handler = sigexit;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	if (sigaction(SIGINT, &action, NULL) != 0)
		reportError("Cannot install SIGINT handler\n");
	if (sigaction(SIGQUIT, &action, NULL) != 0)
		reportError("Cannot install SIGQUIT handler\n");
	if (sigaction(SIGTERM, &action, NULL) != 0)
		reportError("Cannot install SIGTERM handler\n");
	if (sigaction(SIGHUP, &action, NULL) != 0)
		reportError("Cannot install SIGHUP handler\n");
#else

    signal(SIGINT, sigexit);
    signal(SIGTERM, sigexit);
#endif
}

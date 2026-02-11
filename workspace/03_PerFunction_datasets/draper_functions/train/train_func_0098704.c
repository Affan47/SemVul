tidyup_forchild()
{
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sig_childterm;
	if (sigaction(SIGTERM, &sa, NULL)) {

#ifdef DGDEBUG
		std::cerr << "Error resetting signal for SIGTERM" << std::endl;
#endif
		syslog(LOG_ERR, "%s", "Error resetting signal for SIGTERM");
	}
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGUSR1, &sa, NULL)) {

#ifdef DGDEBUG
		std::cerr << "Error resetting signal for SIGUSR1" << std::endl;
#endif
		syslog(LOG_ERR, "%s", "Error resetting signal for SIGUSR1");
	}
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sig_hup;
	if (sigaction(SIGHUP, &sa, NULL)) {

#ifdef DGDEBUG
		std::cerr << "Error resetting signal for SIGHUP" << std::endl;
#endif
		syslog(LOG_ERR, "%s", "Error resetting signal for SIGHUP");
	}


	for (int i = 0; i < o.max_children; i++) {
		if (pids[i].fd != -1) {
			delete childsockets[i];
		}
	}
	delete[]childrenpids;
	delete[]childrenstates;
	delete[]childsockets;
	delete[]pids;
}

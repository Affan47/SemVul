unixWatchAdd(int sig)
	{
		struct sigaction sa;
		sigaction(sig, NULL, &sa);


		if(sa.sa_handler == SIG_IGN)
			return;
		sigemptyset(&(sa.sa_mask));
		sa.sa_flags = 0;
		sa.sa_handler = unixHandler;
		sigaction(sig, &sa, 0);
	}

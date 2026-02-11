set_one_signal_handler(int sig, void (*handler)(int))
{
	struct sigaction sa;
	struct sigaction old_sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = handler;
	sigemptyset(&(sa.sa_mask));
	sa.sa_flags = 0;

	if (sigaction(sig, NULL, &old_sa) == -1) {
		perror("fuse: cannot get old signal handler");
		return -1;
	}

	if (old_sa.sa_handler == SIG_DFL &&
	    sigaction(sig, &sa, NULL) == -1) {
		perror("fuse: cannot set signal handler");
		return -1;
	}
	return 0;
}

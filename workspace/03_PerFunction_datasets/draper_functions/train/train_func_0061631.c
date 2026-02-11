setup_syscall_interruption_support() {
	struct sigaction action;
	sigset_t signal_set;
	int ret;


	sigemptyset(&signal_set);
	do {
		ret = sigprocmask(SIG_SETMASK, &signal_set, NULL);
	} while (ret == -1 && errno == EINTR);

	action.sa_handler = interruption_signal_handler;
	action.sa_flags   = 0;
	sigemptyset(&action.sa_mask);
	do {
		ret = sigaction(INTERRUPTION_SIGNAL, &action, NULL);
	} while (ret == -1 && errno == EINTR);
	do {
		ret = siginterrupt(INTERRUPTION_SIGNAL, 1);
	} while (ret == -1 && errno == EINTR);
}

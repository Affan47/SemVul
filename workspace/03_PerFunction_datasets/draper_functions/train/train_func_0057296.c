register_sig_handler()
{
	struct sigaction sigact;

	sigact.sa_handler = sig_alarm_handler;
	sigact.sa_flags = 0;
	if (sigaction(SIGALRM, &sigact, NULL)) {
		perror("sigaction");
		exit(-1);
	}
	alarm(1);
}

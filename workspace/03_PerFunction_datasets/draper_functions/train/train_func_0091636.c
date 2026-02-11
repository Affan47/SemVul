kill_all(int sig)
{
	int i;

	for (i = 0; i < num_pids; i++) {


		pid_t p = all_pids[i];

		if (p == getpid())
			continue;
		if (p <= 0)
			continue;

		kill(p, sig);
	}
}

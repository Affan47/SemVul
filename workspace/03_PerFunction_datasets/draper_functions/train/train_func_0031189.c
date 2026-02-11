change_runlevel(const char *level)
{
	char *argv[3];
	int pid;
	struct sigaction sa;
	static const char *init_pgm = "/sbin/init";

	pid = fork();
	if (pid < 0) {
		audit_msg(LOG_ALERT,
			"Audit daemon failed to fork switching runlevels");
		return;
	}
	if (pid)
		return;

	sigfillset (&sa.sa_mask);
	sigprocmask (SIG_UNBLOCK, &sa.sa_mask, 0);

	argv[0] = (char *)init_pgm;
	argv[1] = (char *)level;
	argv[2] = NULL;
	execve(init_pgm, argv, NULL);
	audit_msg(LOG_ALERT, "Audit daemon failed to exec %s", init_pgm);
	exit(1);
}

change_runlevel(const char *level)
{
	char *argv[3];
	int pid;

	pid = fork();
	if (pid < 0) {
		syslog(LOG_ALERT,
		       "audisp-remote failed to fork switching runlevels");
		return;
	}
	if (pid)
		return;


	argv[0] = (char *)INIT_PGM;
	argv[1] = (char *)level;
	argv[2] = NULL;
	execve(INIT_PGM, argv, NULL);
	syslog(LOG_ALERT, "audisp-remote failed to exec %s", INIT_PGM);
	exit(1);
}

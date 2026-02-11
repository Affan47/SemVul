forkexec(char *file, List *list, Boolean inchild) {
	int pid, status;
	Vector *env;
	gcdisable();
	env = mkenv();
	pid = efork(!inchild, FALSE);
	if (pid == 0) {
		execve(file, vectorize(list)->vector, env->vector);
		failexec(file, list);
	}
	gcenable();
	status = ewaitfor(pid);
	if ((status & 0xff) == 0) {
		sigint_newline = FALSE;
		SIGCHK();
		sigint_newline = TRUE;
	} else
		SIGCHK();
	printstatus(0, status);
	return mklist(mkterm(mkstatus(status), NULL), NULL);
}

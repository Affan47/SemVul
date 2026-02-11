forkAndRedirectToTee(char *filename) {
	pid_t pid;
	int p[2];

	if (pipe(p) == -1) {

		*filename = '\0';
		return;
	}

	pid = asyncFork();
	if (pid == 0) {
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		execlp("tee", "tee", filename, (const char * const) 0);
		execlp("/usr/bin/tee", "tee", filename, (const char * const) 0);
		execlp("cat", "cat", (const char * const) 0);
		execlp("/bin/cat", "cat", (const char * const) 0);
		execlp("/usr/bin/cat", "cat", (const char * const) 0);
		safePrintErr("ERROR: cannot execute 'tee' or 'cat'; crash log will be lost!\n");
		_exit(1);
	} else if (pid == -1) {
		safePrintErr("ERROR: cannot fork a process for executing 'tee'\n");
		*filename = '\0';
	} else {
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		dup2(p[1], STDERR_FILENO);
	}
}

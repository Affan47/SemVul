spawn(com)
char *com;
{
	int pid;
	static char *sh_base = NULL;

	if (sh_base == NULL) {
		sh_base = strrchr(shell, '/');
		if (sh_base != NULL)
			sh_base++;
		else
			sh_base = shell;
	}


	if (! popup) {
		if (strncmp(com, "exec ", 5) != 0) {
			pid = fork();
			if (pid < 0) {
				fprintf(stderr, "%s: can't fork\n", progname);
				return;
			} else if (pid > 0)
				return;
		} else {
			com += 5;
		}
	}

	close(ConnectionNumber(dpy));
	execl(shell, sh_base, "-c", com, NULL);
	execl("/bin/sh", "sh", "-c", com, NULL);
	_exit(1);
}

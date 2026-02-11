tryexec(IF_FEATURE_SH_STANDALONE(int applet_no,) char *cmd, char **argv, char **envp)
{
	int repeated = 0;

#if ENABLE_FEATURE_SH_STANDALONE
	if (applet_no >= 0) {
		if (APPLET_IS_NOEXEC(applet_no)) {
			clearenv();
			while (*envp)
				putenv(*envp++);
			run_applet_no_and_exit(applet_no, argv);
		}

		execve(bb_busybox_exec_path, argv, envp);


	}
#endif

 repeat:
#ifdef SYSV
	do {
		execve(cmd, argv, envp);
	} while (errno == EINTR);
#else
	execve(cmd, argv, envp);
#endif
	if (repeated) {
		free(argv);
		return;
	}
	if (errno == ENOEXEC) {
		char **ap;
		char **new;

		for (ap = argv; *ap; ap++)
			continue;
		ap = new = ckmalloc((ap - argv + 2) * sizeof(ap[0]));
		ap[1] = cmd;
		ap[0] = cmd = (char *)DEFAULT_SHELL;
		ap += 2;
		argv++;
		while ((*ap++ = *argv++) != NULL)
			continue;
		argv = new;
		repeated++;
		goto repeat;
	}
}

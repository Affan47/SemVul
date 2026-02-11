run_cmd(const gchar *cmd) {
	if (fork() == 0) {
		if (fork() == 0) {
			execl("/bin/sh", "sh", "-c", cmd, NULL);
			exit(0);
		} else
			exit(0);
	} else {
		wait(NULL);
	}
}

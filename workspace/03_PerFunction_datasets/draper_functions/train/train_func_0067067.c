spawn(const char *const cmd[]) {
	ScreenInfo *current_screen = find_current_screen();
	pid_t pid;

	if (current_screen && current_screen->display)
		putenv(current_screen->display);
	if (!(pid = fork())) {
		setsid();
		switch (fork()) {


			case 0: execvp(cmd[0], (char *const *)cmd);
			default: _exit(0);
		}
	}
	if (pid > 0)
		wait(NULL);
}

spawn_grab_buster(void) {
#if LIBVNCSERVER_HAVE_FORK
	pid_t pid;
	int parent = (int) getpid();
	char *dstr = strdup(DisplayString(dpy));

	RAWFB_RET_VOID

	XCloseDisplay_wr(dpy);
	dpy = NULL;

	if ((pid = fork()) > 0) {
		grab_buster_pid = pid;
		if (! quiet) {
			rfbLog("grab_buster pid is: %d\n", (int) pid);
		}
	} else if (pid == -1) {
		fprintf(stderr, "spawn_grab_buster: could not fork\n");
		rfbLogPerror("fork");
	} else {
		signal(SIGHUP,  SIG_DFL);
		signal(SIGINT,  SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);

		grab_buster_watch(parent, dstr);
		exit(0);
	}

	dpy = XOpenDisplay_wr(dstr);
	if (!dpy) {
		rfbLog("failed to reopen display %s in spawn_grab_buster\n",
		    dstr);
		exit(1);
	}
#endif
}

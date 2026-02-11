try_local_chat_window(void) {
	int i, port, lsock;
	char cmd[100];
	struct sockaddr_in addr;
	pid_t pid = -1;
#ifdef __hpux
	int addrlen = sizeof(addr);
#else
	socklen_t addrlen = sizeof(addr);
#endif

	for (i = 0; i < 90; i++)  {

		port = 7300 + i;

		lsock = listen_tcp(port, htonl(INADDR_LOOPBACK), 0);
		if (lsock >= 0) {
			break;
		}
		port = 0;
	}

	if (port == 0) {
		return;
	}


	sprintf(cmd, "ssvnc -cmd VNC://localhost:%d -chatonly", port);

#if LIBVNCSERVER_HAVE_FORK
	pid = fork();
#endif

	if (pid == -1) {
		perror("fork");
		return;
	} else if (pid == 0) {
		char *args[4];
		int d;
		args[0] = "/bin/sh";
		args[1] = "-c";

		args[2] = cmd;
		args[3] = NULL;

		set_env("VNCVIEWER_PASSWORD", "moo");
#if !NO_X11
		if (dpy != NULL) {
			set_env("DISPLAY", DisplayString(dpy));
		}
#endif
		for (d = 3; d < 256; d++) {
			close(d);
		}

		execvp(args[0], args);
		perror("exec");
		exit(1);
	} else {
		int i, sock = -1;
		rfbNewClientHookPtr new_save;

		signal(SIGALRM, wsock_timeout);
		wsock_timeout_sock = lsock;

		alarm(10);
		sock = accept(lsock, (struct sockaddr *)&addr, &addrlen);
		alarm(0);

		signal(SIGALRM, SIG_DFL);
		close(lsock);

		if (sock < 0) {
			return;
		}


		new_save = screen->newClientHook;
		screen->newClientHook = new_client_chat_helper;

		chat_window_client = create_new_client(sock, 1);

		screen->newClientHook = new_save;

		if (chat_window_client != NULL) {
			rfbPasswordCheckProcPtr pwchk_save = screen->passwordCheck;
			rfbBool save_shared1 = screen->alwaysShared;
			rfbBool save_shared2 = screen->neverShared;

			screen->alwaysShared = TRUE;
			screen->neverShared  = FALSE;

			screen->passwordCheck = password_check_chat_helper;
			for (i=0; i<30; i++) {
				rfbPE(-1);
				if (!chat_window_client) {
					break;
				}
				if (chat_window_client->state == RFB_NORMAL) {
					break;
				}
			}

			screen->passwordCheck = pwchk_save;
			screen->alwaysShared  = save_shared1;
			screen->neverShared   = save_shared2;
		}
	}
}

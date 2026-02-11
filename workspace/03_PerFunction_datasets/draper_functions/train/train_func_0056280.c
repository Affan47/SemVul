sesssigchild_handler(int UNUSED(dummy)) {

	int status;
	pid_t pid;
	unsigned int i;
	struct sigaction sa_chld;
	struct exitinfo *exit = NULL;

	TRACE(("enter sigchld handler"))
	while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
		TRACE(("sigchld handler: pid %d", pid))

		exit = NULL;

		for (i = 0; i < svr_ses.childpidsize; i++) {
			if (svr_ses.childpids[i].pid == pid) {
				TRACE(("found match session"));
				exit = &svr_ses.childpids[i].chansess->exit;
				break;
			}
		}


		if (exit == NULL) {
			TRACE(("using lastexit"));
			exit = &svr_ses.lastexit;
		}

		exit->exitpid = pid;
		if (WIFEXITED(status)) {
			exit->exitstatus = WEXITSTATUS(status);
		}
		if (WIFSIGNALED(status)) {
			exit->exitsignal = WTERMSIG(status);
#if !defined(AIX) && defined(WCOREDUMP)
			exit->exitcore = WCOREDUMP(status);
#else
			exit->exitcore = 0;
#endif
		} else {

			exit->exitsignal = -1;
		}


		while (1) {


			if (write(ses.signal_pipe[1], &ses.isserver, 1) == 1
					|| errno != EINTR) {
				break;
			}
		}
	}

	sa_chld.sa_handler = sesssigchild_handler;
	sa_chld.sa_flags = SA_NOCLDSTOP;
	sigaction(SIGCHLD, &sa_chld, NULL);
	TRACE(("leave sigchld handler"))
}

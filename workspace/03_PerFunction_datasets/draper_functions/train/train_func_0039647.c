onsig(int signo)
{
	if (signo == SIGCHLD) {
		gotsigchld = 1;
		if (!trap[SIGCHLD])
			return;
	}

	gotsig[signo - 1] = 1;
	pendingsigs = signo;

	if (signo == SIGINT && !trap[SIGINT]) {
		if (!suppressint)
			onint();
		intpending = 1;
	}
}

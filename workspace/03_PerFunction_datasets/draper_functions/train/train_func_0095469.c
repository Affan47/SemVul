setsignal(int signo)
{
	char *t;
	char cur_act, new_act;
	struct sigaction act;

	t = trap[signo];
	new_act = S_DFL;
	if (t != NULL) {
		new_act = S_CATCH;
		if (t[0] == '\0')
			new_act = S_IGN;
	}

	if (rootshell && new_act == S_DFL) {
		switch (signo) {
		case SIGINT:
			if (iflag || minusc || sflag == 0)
				new_act = S_CATCH;
			break;
		case SIGQUIT:
#if DEBUG
			if (debug)
				break;
#endif


			new_act = S_IGN;
			break;
		case SIGTERM:
			if (iflag)
				new_act = S_IGN;
			break;
#if JOBS
		case SIGTSTP:
		case SIGTTOU:
			if (mflag)
				new_act = S_IGN;
			break;
#endif
		}
	}


	t = &sigmode[signo - 1];
	cur_act = *t;
	if (cur_act == 0) {

		if (sigaction(signo, NULL, &act)) {


			return;
		}
		if (act.sa_handler == SIG_IGN) {
			cur_act = S_HARD_IGN;
			if (mflag
			 && (signo == SIGTSTP || signo == SIGTTIN || signo == SIGTTOU)
			) {
				cur_act = S_IGN;
			}
		}
	}
	if (cur_act == S_HARD_IGN || cur_act == new_act)
		return;

	act.sa_handler = SIG_DFL;
	switch (new_act) {
	case S_CATCH:
		act.sa_handler = signal_handler;
		act.sa_flags = 0;
		sigfillset(&act.sa_mask);
		break;
	case S_IGN:
		act.sa_handler = SIG_IGN;
		break;
	}
	sigaction_set(signo, &act);

	*t = new_act;
}

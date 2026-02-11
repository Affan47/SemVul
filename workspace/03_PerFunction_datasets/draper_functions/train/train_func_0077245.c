trapcmd(int argc, char **argv)
{
	char *action;
	char **ap;
	int signo;

	nextopt(nullstr);
	ap = argptr;
	if (!*ap) {
		for (signo = 0 ; signo < NSIG ; signo++) {
			if (trap[signo] != NULL) {
				out1fmt(
					"trap -- %s %s\n",
					single_quote(trap[signo]),
					signal_names[signo]
				);
			}
		}
		return 0;
	}
	if (!ap[1])
		action = NULL;
	else
		action = *ap++;
	while (*ap) {
		if ((signo = decode_signal(*ap, 0)) < 0) {
			outfmt(out2, "trap: %s: bad trap\n", *ap);
			return 1;
		}
		INTOFF;
		if (action) {
			if (action[0] == '-' && action[1] == '\0')
				action = NULL;
			else {
				if (*action)
					trapcnt++;
				action = savestr(action);
			}
		}
		if (trap[signo]) {
			if (*trap[signo])
				trapcnt--;
			ckfree(trap[signo]);
		}
		trap[signo] = action;
		if (signo != 0)
			setsignal(signo);
		INTON;
		ap++;
	}
	return 0;
}

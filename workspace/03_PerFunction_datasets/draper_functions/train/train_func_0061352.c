sprintsigmask(const char *str, sigset_t *mask, int rt)

{
	int i, nsigs;
	int maxsigs;
	const char *format;
	char *s;
	static char outstr[8 * sizeof(sigset_t) * 8];

	strcpy(outstr, str);
	s = outstr + strlen(outstr);
	nsigs = 0;
	maxsigs = nsignals;
#ifdef __SIGRTMAX
	if (rt)
		maxsigs = __SIGRTMAX;
#endif
	for (i = 1; i < maxsigs; i++) {
		if (sigismember(mask, i) == 1)
			nsigs++;
	}
	if (nsigs >= nsignals * 2 / 3) {
		*s++ = '~';
		for (i = 1; i < maxsigs; i++) {
			switch (sigismember(mask, i)) {
			case 1:
				sigdelset(mask, i);
				break;
			case 0:
				sigaddset(mask, i);
				break;
			}
		}
	}
	format = "%s";
	*s++ = '[';
	for (i = 1; i < maxsigs; i++) {
		if (sigismember(mask, i) == 1) {


			if (i < nsignals) {
				sprintf(s, format, signalent[i] + 3);
			}
#ifdef SIGRTMIN
			else if (i >= __SIGRTMIN && i <= __SIGRTMAX) {
				char tsig[40];
				sprintf(tsig, "RT_%u", i - __SIGRTMIN);
				sprintf(s, format, tsig);
			}
#endif
			else {
				char tsig[32];
				sprintf(tsig, "%u", i);
				sprintf(s, format, tsig);
			}
			s += strlen(s);
			format = " %s";
		}
	}
	*s++ = ']';
	*s = '\0';
	return outstr;
}

shiftcmd(int argc UNUSED_PARAM, char **argv)
{
	int n;
	char **ap1, **ap2;

	n = 1;
	if (argv[1])
		n = number(argv[1]);
	if (n > shellparam.nparam)
		n = 0;
	INT_OFF;
	shellparam.nparam -= n;
	for (ap1 = shellparam.p; --n >= 0; ap1++) {
		if (shellparam.malloced)
			free(*ap1);
	}
	ap2 = shellparam.p;
	while ((*ap2++ = *ap1++) != NULL)
		continue;
#if ENABLE_ASH_GETOPTS
	shellparam.optind = 1;
	shellparam.optoff = -1;
#endif
	INT_ON;
	return 0;
}

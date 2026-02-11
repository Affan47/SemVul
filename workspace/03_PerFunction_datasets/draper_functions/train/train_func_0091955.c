imap_search1(const char *spec, int f)
{
	sighandler_type	saveint, savepipe;
	enum okay	ok = STOP;

	(void)&saveint;
	(void)&savepipe;
	(void)&ok;
	if (mb.mb_type != MB_IMAP)
		return STOP;
	verbose = value("verbose") != NULL;
	imaplock = 1;
	if ((saveint = safe_signal(SIGINT, SIG_IGN)) != SIG_IGN)
		safe_signal(SIGINT, maincatch);
	savepipe = safe_signal(SIGPIPE, SIG_IGN);
	if (sigsetjmp(imapjmp, 1) == 0) {
		if (savepipe != SIG_IGN)
			safe_signal(SIGPIPE, imapcatch);
		ok = imap_search2(&mb, message, msgCount, spec, f);
	}
	safe_signal(SIGINT, saveint);
	safe_signal(SIGPIPE, savepipe);
	imaplock = 0;
	if (interrupts)
		onintr(0);
	return ok;
}

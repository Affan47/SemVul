imap_folders(const char *name, int strip)
{
	sighandler_type	saveint, savepipe;
	const char	*fold, *cp, *sp;
	char	*tempfn;
	FILE	*fp;
	int	columnize = is_a_tty[1];

	(void)&saveint;
	(void)&savepipe;
	(void)&fp;
	(void)&fold;
	cp = protbase(name);
	sp = mb.mb_imap_account;
	if (strcmp(cp, sp)) {
		fprintf(stderr, "Cannot list folders on other than the "
				"current IMAP account,\n\"%s\". "
				"Try \"folders @\".\n", sp);
		return;
	}
	fold = protfile(name);
	if (columnize) {
		if ((fp = Ftemp(&tempfn, "Ri", "w+", 0600, 1)) == NULL) {
			perror("tmpfile");
			return;
		}
		rm(tempfn);
		Ftfree(&tempfn);
	} else
		fp = stdout;
	imaplock = 1;
	if ((saveint = safe_signal(SIGINT, SIG_IGN)) != SIG_IGN)
		safe_signal(SIGINT, maincatch);
	savepipe = safe_signal(SIGPIPE, SIG_IGN);
	if (sigsetjmp(imapjmp, 1))
		goto out;
	if (savepipe != SIG_IGN)
		safe_signal(SIGPIPE, imapcatch);
	if (mb.mb_type == MB_CACHE)
		cache_list(&mb, fold, strip, fp);
	else
		imap_list(&mb, fold, strip, fp);
	imaplock = 0;
	if (interrupts) {
		if (columnize)
			Fclose(fp);
		onintr(0);
	}
	fflush(fp);
	if (columnize) {
		rewind(fp);
		if (fsize(fp) > 0)
			dopr(fp);
		else
			fprintf(stderr, "Folder not found.\n");
	}
out:
	safe_signal(SIGINT, saveint);
	safe_signal(SIGPIPE, savepipe);
	if (columnize)
		Fclose(fp);
}

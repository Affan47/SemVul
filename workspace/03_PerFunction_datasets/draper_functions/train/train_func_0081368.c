maildir_setfile(const char *name, int newmail, int isedit)
{
	sighandler_type	saveint;
	struct cw	cw;
	int	i = -1, omsgCount;

	(void)&saveint;
	(void)&i;
	omsgCount = msgCount;
	if (cwget(&cw) == STOP) {
		fprintf(stderr, "Fatal: Cannot open current directory\n");
		return -1;
	}
	if (!newmail)
		quit();
	saveint = safe_signal(SIGINT, SIG_IGN);
	if (chdir(name) < 0) {
		fprintf(stderr, "Cannot change directory to \"%s\".\n", name);
		cwrelse(&cw);
		return -1;
	}
	if (!newmail) {
		edit = isedit;
		if (mb.mb_itf) {
			fclose(mb.mb_itf);
			mb.mb_itf = NULL;
		}
		if (mb.mb_otf) {
			fclose(mb.mb_otf);
			mb.mb_otf = NULL;
		}
		initbox(name);
		mb.mb_type = MB_MAILDIR;
	}
	mdtable = NULL;
	if (sigsetjmp(maildirjmp, 1) == 0) {
		if (newmail)
			mktable();
		if (saveint != SIG_IGN)
			safe_signal(SIGINT, maildircatch);
		i = maildir_setfile1(name, newmail, omsgCount);
	}
	if (newmail)
		free(mdtable);
	safe_signal(SIGINT, saveint);
	if (i < 0) {
		mb.mb_type = MB_VOID;
		*mailname = '\0';
		msgCount = 0;
	}
	if (cwret(&cw) == STOP) {
		fputs("Fatal: Cannot change back to current directory.\n",
				stderr);
		abort();
	}
	cwrelse(&cw);
	setmsize(msgCount);
	if (newmail && mb.mb_sorted && msgCount > omsgCount) {
		mb.mb_threaded = 0;
		sort((void *)-1);
	}
	if (!newmail)
		sawcom = 0;
	if (!newmail && !edit && msgCount == 0) {
		if (mb.mb_type == MB_MAILDIR && value("emptystart") == NULL)
			fprintf(stderr, "No mail at %s\n", name);
		return 1;
	}
	if (newmail && msgCount > omsgCount)
		newmailinfo(omsgCount);
	return 0;
}

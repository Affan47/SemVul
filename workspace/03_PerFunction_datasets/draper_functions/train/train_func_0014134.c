chkmail(void)
{
	const char *mpath;
	char *p;
	char *q;
	time_t *mtp;
	struct stackmark smark;
	struct stat64 statb;

	setstackmark(&smark);
	mpath = mpathset() ? mpathval() : mailval();
	for (mtp = mailtime; mtp < mailtime + MAXMBOXES; mtp++) {
		p = padvance(&mpath, nullstr);
		if (p == NULL)
			break;
		if (*p == '\0')
			continue;
		for (q = p ; *q ; q++);
#ifdef DEBUG
		if (q[-1] != '/')
			abort();
#endif
		q[-1] = '\0';
		if (stat64(p, &statb) < 0) {
			*mtp = 0;
			continue;
		}
		if (!changed && statb.st_mtime != *mtp) {
			outfmt(
				&errout, snlfmt,
				pathopt ? pathopt : "you have mail"
			);
		}
		*mtp = statb.st_mtime;
	}
	changed = 0;
	popstackmark(&smark);
}

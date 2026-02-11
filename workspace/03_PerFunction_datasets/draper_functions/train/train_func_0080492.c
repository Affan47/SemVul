imap_newmail(int autoinc)
{
	if (autoinc && had_exists < 0 && had_expunge < 0) {
		verbose = value("verbose") != NULL;
		imaplock = 1;
		imap_noop();
		imaplock = 0;
	}
	if (had_exists == msgCount && had_expunge < 0)


		had_exists = -1;
	return had_expunge >= 0 ? 2 : had_exists >= 0 ? 1 : 0;
}

open_temp(hashp)
	HTAB *hashp;
{
	sigset_t set, oset;
	static char namestr[] = "_hashXXXXXX";


	(void)sigfillset(&set);
	(void)sigprocmask(SIG_BLOCK, &set, &oset);
	if ((hashp->fp = mkstemp(namestr)) != -1) {
		(void)unlink(namestr);
		(void)fcntl(hashp->fp, F_SETFD, 1);
	}
	(void)sigprocmask(SIG_SETMASK, &oset, (sigset_t *)NULL);
	return (hashp->fp != -1 ? 0 : -1);
}

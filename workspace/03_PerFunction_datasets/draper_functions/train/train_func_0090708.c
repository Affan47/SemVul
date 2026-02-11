dosstat(path, stp)
CONST char *path;
struct stat *stp;
{
	char *cp;
	int dd;

	if ((dd = getdent(path, NULL)) < 0) return(seterrno(doserrno));
	stp -> st_dev = dd;
	stp -> st_ino = clust32(&(devlist[dd]), dd2dentp(dd));
	stp -> st_mode = getunixmode(dd2dentp(dd) -> attr);
	stp -> st_nlink = 1;
	stp -> st_uid = (uid_t)-1;
	stp -> st_gid = (gid_t)-1;
	stp -> st_size = byte2dword(dd2dentp(dd) -> size);
	stp -> st_atime =
	stp -> st_mtime =
	stp -> st_ctime = getunixtime(byte2word(dd2dentp(dd) -> date),
		byte2word(dd2dentp(dd) -> time));
#if	!MSDOS && defined (UF_SETTABLE) && defined (SF_SETTABLE)
	stp -> st_flags = (u_long)0;
#endif
	dosclosedev(dd);

	if ((stp -> st_mode & S_IFMT) != S_IFDIR
	&& (cp = Xstrrchr(path, '.')) && strlen(++cp) == 3) {
		if (!Xstrcasecmp(cp, EXTCOM)
		|| !Xstrcasecmp(cp, EXTEXE) || !Xstrcasecmp(cp, EXTBAT))
			stp -> st_mode |= S_IEXEC_ALL;
	}

	return(0);
}

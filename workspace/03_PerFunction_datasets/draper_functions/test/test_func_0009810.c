launcher(VOID_A)
{
#ifndef	_NOBROWSE
	CONST char *cp;
	int flags;
#endif
	reg_ex_t *re;
	int i, n;

#ifndef	_NOBROWSE
	if (browselist) {
		n = browselevel;
		cp = browselist[n].ext;
		flags = (F_NOCONFIRM | F_ARGSET | F_NOADDOPT | F_IGNORELIST);

		pushbrowsevar(filelist[filepos].name);
		if (cp && !(browselist[n].flags & LF_FILENOPREP))
			execusercomm(cp, filelist[filepos].name, flags);

		if (browselist[n + 1].comm
		&& !(browselist[n].flags & LF_FILELOOP))
			n++;
		if (dolaunch(&(browselist[n]), flags) < 0
		|| !isarchbr(&(browselist[n]))) {
			popbrowsevar();
			return(-1);
		}
		browselevel = n;
		return(1);
	}
#endif

	for (i = 0; i < maxlaunch; i++) {
#ifndef	PATHNOCASE
		if (launchlist[i].flags & LF_IGNORECASE) pathignorecase++;
#endif
		re = regexp_init(launchlist[i].ext, -1);
		n = regexp_exec(re, filelist[filepos].name, 0);
		regexp_free(re);
#ifndef	PATHNOCASE
		if (launchlist[i].flags & LF_IGNORECASE) pathignorecase--;
#endif
		if (n) break;
	}
	if (i >= maxlaunch) return(0);

	return(dolaunch(&(launchlist[i]), F_NOCONFIRM | F_IGNORELIST));
}

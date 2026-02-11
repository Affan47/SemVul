execute_file(arg)
CONST char *arg;
{
#if	!defined (_NOARCHIVE) || defined (DEP_PSEUDOPATH)
	char *dir;
#endif
#ifndef	CWDINPATH
	char *tmp;
#endif
#ifdef	DEP_PSEUDOPATH
	int drive;
#endif
	char *com;
	int ret, len;

#if	!defined (_NOARCHIVE) && !defined (_NOBROWSE)
	if (browselist) return(warning_bell(arg));
#endif

#if	!defined (_NOARCHIVE) || defined (DEP_PSEUDOPATH)
	dir = NULL;
#endif
#ifdef	DEP_PSEUDOPATH
	drive = 0;
#endif
#ifdef	CWDINPATH
	len = (!isdir(&(filelist[filepos])) && isexec(&(filelist[filepos])))
		? strlen(filelist[filepos].name) + 1 : 0;
	Xttyiomode(1);
	com = inputshellloop(len, filelist[filepos].name);
	Xttyiomode(0);
#else
	if (isdir(&(filelist[filepos])) || !isexec(&(filelist[filepos]))) {
		len = 0;
		tmp = filelist[filepos].name;
	}
	else {
		len = strlen(filelist[filepos].name) + 2 + 1;
		tmp = Xmalloc(len + 1);
		tmp[0] = '.';
		tmp[1] = _SC_;
		Xstrcpy(&(tmp[2]), filelist[filepos].name);
	}
	Xttyiomode(1);
	com = inputshellloop(len, tmp);
	Xttyiomode(0);
	if (tmp != filelist[filepos].name) Xfree(tmp);
#endif
	if (!com) return(FNC_CANCEL);
	if (!*com) {
		execshell();
		Xfree(com);
		return(FNC_EFFECT);
	}

#ifndef	_NOARCHIVE
	if (archivefile) {
		if (!(dir = tmpunpack(1))) ret = -1;
		else {
			ret = ptyusercomm(com, filelist[filepos].name,
				F_ARGSET | F_IGNORELIST);
			removetmp(dir, NULL);
		}
	}
	else
#endif
#ifdef	DEP_PSEUDOPATH
	if ((drive = tmpdosdupl(nullstr, &dir, 1)) < 0) ret = -1;
	else if (drive) {
		ret = ptyusercomm(com, filelist[filepos].name,
			F_ARGSET | F_IGNORELIST);
		removetmp(dir, filelist[filepos].name);
	}
	else
#endif
	{
		ret = ptyusercomm(com, filelist[filepos].name, F_ARGSET);
	}
	ret = evalstatus(ret);
	Xfree(com);

	return(ret);
}

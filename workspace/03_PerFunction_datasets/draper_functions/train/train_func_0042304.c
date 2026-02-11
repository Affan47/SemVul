dolaunch(list, flags)
lsparse_t *list;
int flags;
{
#ifdef	DEP_PSEUDOPATH
	int drive;
#endif
	CONST char *cp;
	char *tmpdir;

	tmpdir = NULL;
#ifdef	DEP_PSEUDOPATH
	drive = 0;
#endif

	if (flags & F_ARGSET) ;
	else if (archivefile) {
		if (!(tmpdir = tmpunpack(1))) {
			Xputterm(T_BELL);
			return(-1);
		}
	}
#ifdef	DEP_PSEUDOPATH
	else if ((drive = tmpdosdupl(nullstr, &tmpdir, 1)) < 0) {
		Xputterm(T_BELL);
		return(-1);
	}
#endif

	if (!isarchbr(list)) {
		ptyusercomm(list -> comm, filelist[filepos].name, flags);
		if (flags & F_ARGSET) ;
#ifdef	DEP_PSEUDOPATH
		else if (drive) removetmp(tmpdir, filelist[filepos].name);
#endif
		else if (archivefile) removetmp(tmpdir, NULL);
		return(1);
	}

	pusharchdupl();
	if (flags & F_ARGSET) ;
#ifdef	DEP_PSEUDOPATH
	else if (drive) {
		archduplp -> v_fullpath = Xstrdup(fullpath);
		Xstrcpy(fullpath, tmpdir);
	}
#endif
	else if (archivefile) {
		archduplp -> v_fullpath = Xstrdup(fullpath);
		Xstrcpy(fullpath, tmpdir);
		if (*archivedir) {
			Xstrcpy(strcatdelim(fullpath), archivedir);
			archduplp -> v_archivedir = Xstrdup(archivedir);
		}
	}
	cp = (filelist && filepos < maxfile) ? filelist[filepos].name : NULL;
	if (!cp) cp = nullstr;
	if (archivefile) maxfile = 0;
	*archivedir = '\0';
	archivefile = Xstrdup(cp);
	archtmpdir = tmpdir;
	launchp = list;
	arcflist = NULL;
	maxarcf = 0;
#ifdef	DEP_PSEUDOPATH
	archdrive = drive;
#endif
#ifndef	_NOTREE
	treepath = NULL;
#endif
	findpattern = NULL;
	while (maxfile > 0) Xfree(filelist[--maxfile].name);
#if	FD >= 2
	if (sorttype < 200) sorton = 0;
#else
	sorton = 0;
#endif

	if (readarchive(archivefile, launchp, flags) < 0) {
		arcflist = NULL;
		poparchdupl();
		return(-1);
	}
	maxfile = filepos = 0;

	return(1);
}

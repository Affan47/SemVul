shutwin(n)
int n;
{
	int i, dupwin;

	dupwin = win;
	win = n;
# ifndef	_NOARCHIVE
	while (archivefile) escapearch(1);
	Xfree(winvar[win].v_archivedir);
	winvar[win].v_archivedir = NULL;
# endif
	Xfree(winvar[win].v_fullpath);
	winvar[win].v_fullpath = NULL;
	setlastfile(NULL);
	if (filelist) {
		for (i = 0; i < maxfile; i++) Xfree(filelist[i].name);
		Xfree(filelist);
		filelist = NULL;
	}
	maxfile = maxent = filepos = sorton = dispmode = 0;
	Xfree(findpattern);
	findpattern = NULL;
# ifdef	DEP_PTY
	killpty(win, NULL);
# endif
	win = dupwin;

	return(n);
}

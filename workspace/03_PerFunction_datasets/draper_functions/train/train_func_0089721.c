setdir(int name)
{
    char *dirstring = dirs[name];
    char *s = NULL;
    if (dirstring[0] == '.' && !dirstring[1]) {

	s = mystrdup(currdir);
    } else if (dirstring[0] && dirstring[1] && dirstring[0] == '.'
	       && dirstring[1] == '.' && !dirstring[2]) {
	int i = (int) strlen(currdir);
	s = (char *) malloc((int) strlen(dirstring) +
			    (int) strlen(currdir) + 2);
	strcpy(s, currdir);
	for (;
	     i >= 0 && s[i] != '/' && s[i] != '\\' && s[i] != XIO_PATHSEP;
	     i--);
	if (i < 0)
	    free(s), s = NULL;
	else
	    s[i] = 0;
    }
    if (s == NULL) {
	int i = (int) strlen(currdir);
	s = (char *) malloc((int) strlen(dirstring) +
			    (int) strlen(currdir) + 2);
	strcpy(s, currdir);
	if (currdir[i - 1] != '/' && currdir[i - 1] != '\\'
	    && currdir[i - 1] != XIO_PATHSEP)
	    strcat(s, XIO_PATHSEPSTR);
	strcat(s, dirstring);
	if (!s[0])
	    s[0] = XIO_PATHSEP, s[1] = 0;
    }
    free(currdir);
#ifdef DRIVES
    if (strlen(s) == 2
	&& ((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))
	&& s[1] == ':')
	s[2] = XIO_PATHSEP, s[3] = 0;
#endif
    currdir = s;
    ui_closetext(dir);
    dir =
	ui_opentext(filex + 2 * BORDERWIDTH, DIRSTART + BORDERHEIGHT,
		    filewidth - 4 * BORDERWIDTH, currdir);
    ui_freenames();
    ui_buildnames(LISTWIDTH);
    dirstart = 0;
    selecteddir = 0;
    namestart = 0;
    selectedname = 0;
    uih->display = 1;
}

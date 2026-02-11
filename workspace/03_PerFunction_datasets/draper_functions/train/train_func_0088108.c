xio_getfiles(xio_constpath path1, char ***names, char ***dirs,
	     int *nnames2, int *ndirs2)
{
#ifdef HAVE_DIRENT_H
    char *path = xio_fixpath(path1);
    int maxnames = 200, maxdirs = 200;
    int nnames = 0, ndirs = 0;
    DIR *dir = opendir(path);
    struct stat buf;
    char buff[4096];
    int pathlen;
    struct dirent *e;
    if (dir == NULL)
	return 0;
    *nnames2 = 0;
    *ndirs2 = 0;
    e = readdir(dir);
    strcpy(buff, path);
    pathlen = (int) strlen(path);
    if (buff[pathlen - 1] != XIO_PATHSEP)
	buff[pathlen] = XIO_PATHSEP;
    else
	pathlen--;
    *names = (char **) malloc(maxnames * sizeof(**names));
    *dirs = (char **) malloc(maxdirs * sizeof(**dirs));
    free(path);
    while (e != NULL) {
	char *n = mystrdup(e->d_name);
	strcpy(buff + pathlen + 1, e->d_name);
	stat(buff, &buf);
	if (S_ISDIR(buf.st_mode)) {
	    if (ndirs == maxdirs)
		maxdirs *= 2, *dirs =
		    (char **) realloc(*dirs, maxdirs * sizeof(**dirs));
	    (*dirs)[ndirs] = n;
	    ndirs++;
	} else {
	    if (nnames == maxnames)
		maxnames *= 2, *names =
		    (char **) realloc(*names, maxnames * sizeof(**names));
	    (*names)[nnames] = n;
	    nnames++;
	}
	e = readdir(dir);
    }
    if (nnames)
	*names = (char **) realloc(*names, nnames * sizeof(**names));
    else
	free(*names), *names = NULL;
    if (ndirs)
	*dirs = (char **) realloc(*dirs, ndirs * sizeof(**dirs));
    else
	free(*dirs), *dirs = NULL;
    *nnames2 = nnames;
    *ndirs2 = ndirs;
    closedir(dir);
    return 1;
#else
    *nnames2 = *ndirs2 = 0;
    return 0;
#endif
}

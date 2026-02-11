xio_getrandomexample(xio_path name)
{
#ifdef HAVE_DIRENT_H
    static const char *const paths[] = {
	EXAMPLESPATH,
	"\01" XIO_PATHSEPSTR "examples",

	"\01" XIO_PATHSEPSTR ".." XIO_PATHSEPSTR "examples",
	"." XIO_PATHSEPSTR "examples",

	".." XIO_PATHSEPSTR "examples",

	XIO_EMPTYPATH,
    };
    int i = -1, p;
    DIR *d = NULL;
    xio_file f;
    struct dirent *dir;
    int n;
    int max = 0;
    char *realpath = NULL;

    for (p = 0; p < (int) (sizeof(paths) / sizeof(char *)) && d == NULL;
	 p++) {
	char *pp = xio_fixpath(paths[p]);
	d = opendir(pp);
	free(pp);
	if (d != NULL) {
	    realpath = xio_fixpath(paths[p]);
	    max = 800 - (int) strlen(realpath);
	    for (i = 0; (dir = readdir(d)) != NULL; i++) {
		int s = (int) strlen(dir->d_name);
		if (s > max || s < 4
		    || strcmp(".xpf", dir->d_name + s - 4))
		    i--;

	    }
	    if (!i) {

		closedir(d);
		free(realpath);
		d = NULL;
		continue;
	    }
	    break;
	}
    }
    if (d == NULL) {

	return NULL;
    }


    rewinddir(d);
    dir = NULL;
    n = (int) ((number_t) i * rand() / (RAND_MAX + 1.0));

    for (i = 0; i <= n; i++) {
	int s;
	do {

	    dir = readdir(d);
	    if (dir == NULL) {

		closedir(d);
		free(realpath);
		return NULL;
	    }
	    s = (int) strlen(dir->d_name);
	}
	while (s > max || s < 4 || strcmp(".xpf", dir->d_name + s - 4));
    }
    if (dir == NULL) {

	closedir(d);
	free(realpath);
	return NULL;
    }
    strcpy(name, realpath);
    if (name[strlen(name) - 1] != XIO_PATHSEP)
	strcat(name, XIO_PATHSEPSTR);
    strcat(name, dir->d_name);
    closedir(d);


    f = xio_ropen(name);
    free(realpath);
    return (f);
#else
    return NULL;
#endif
}

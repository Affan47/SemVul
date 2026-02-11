plGetName(const char *dir, const char *subdir, const char *filename,
	  char **filespec)
{
    int lfilespec;


    free_mem(*filespec);
    lfilespec = 10;
    lfilespec = strlen(dir) + strlen(subdir) + strlen(filename) + 10;
    *filespec = (char *) malloc(lfilespec);

    strcpy(*filespec, dir);

    if (*subdir != '\0') {
	strcat_delim(*filespec);
	strcat(*filespec, subdir);
    }
    if (*filename != '\0') {
	strcat_delim(*filespec);
	strcat(*filespec, filename);
    }
}

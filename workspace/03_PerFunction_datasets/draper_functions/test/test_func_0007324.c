countscripts(char *name)
{
    DIR *dp;
    struct dirent *dir;
    size_t length;
    int number=0;
    char myname[1024];

    snprintf(myname, 1023, "%s.script", name);

    if ((dp = opendir(".")) == NULL) {
	return -1;
    }

    while ((dir=readdir(dp)) != NULL) {
	length=strlen(dir->d_name);
	if (length >= strlen(".script") &&
	    (strcmp(dir->d_name + (length - 7), ".script") == 0)) {

	    if (strcmp(myname, dir->d_name) != 0) {

		number++;
	    }
	}
    }

    closedir(dp);

    return number;
}

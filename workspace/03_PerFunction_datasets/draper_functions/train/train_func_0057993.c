fakeactive(void)
{
    DIR *d;
    struct dirent *de;
    DIR *ng;
    struct dirent *nga;
    long unsigned int i;
    long unsigned first, last;
    char *p;
    char s[SIZE_s+1];
    struct stat st;
    time_t age;

    killactiveread();
    xsnprintf(s, SIZE_s, "%s/interesting.groups", spooldir);
    d = opendir(s);
    if (!d) {
	syslog(LOG_ERR, "cannot open directory %s: %m", s);
	return;
    }

    while ((de = readdir(d))) {
	if (isalnum((unsigned char)*(de->d_name)) &&
	    chdirgroup(de->d_name, FALSE)) {


	    first = ULONG_MAX;
	    last = 0;

	    ng = opendir(".");
	    while ((nga = readdir(ng)) != NULL) {
		if (isdigit((unsigned char)*(nga->d_name))) {
		    p = NULL;
		    i = strtoul(nga->d_name, &p, 10);
		    if (*p == '\0') {
			if (i < first)
			    first = i;
			if (i > last)
			    last = i;
		    }
		}
	    }
	    if (first > last) {
		first = 1;
		last = 1;
	    }
	    closedir(ng);
	    if (debugmode)
		syslog(LOG_DEBUG, "parsed directory %s: first %lu, last %lu",
		       de->d_name, first, last);
	    if (0 == stat(".", &st))
		age = st.st_ctime;
	    else
		age = 0;
	    insertgroup(de->d_name, first, last, age);
	}
    }
    mergegroups();

    closedir(d);
}

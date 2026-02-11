rereadactive(void)
{
    struct stat st;
    char s[SIZE_s+1];

    (void)xsnprintf(s, SIZE_s, "%s/leaf.node/groupinfo", spooldir);

    if ((!stat(s, &st) && (st.st_mtime > activetime)) || (active == NULL)) {
	char *grouptmp = NULL;
	if (debugmode)
	    syslog(LOG_DEBUG, "rereading %s", s);
	if (group) {
	    grouptmp = critstrdup(group->name, "rereadactive");
	}
	readactive();
	if (activesize == 0)
	    fakeactive();
	else
	    activetime = st.st_mtime;
	if (grouptmp) {
	    group = findgroup(grouptmp);
	    xovergroup = NULL;
	    free(grouptmp);
	}
    }
}

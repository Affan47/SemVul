CheckNeedReloadDB(bool force)
{
    static time_t lastcheck, oldlastcheck, now;
    struct stat sb;
    char *fname;

    now = time(NULL);
    if (!force && lastcheck + RELOAD_TIME_CHECK > now)
        return;

    oldlastcheck = lastcheck;
    lastcheck = now;

    fname = concatpath(innconf->pathspool, _PATH_TRADSPOOLNGDB);
    if (stat(fname, &sb) < 0) {
	free(fname);
	return;
    }
    free(fname);
    if (sb.st_mtime > oldlastcheck) {

	ReadDBFile();
    }
}

updateactive(void)
{
    struct stat st;
    struct utimbuf buf;
    FILE *f;
    char *s = activeread();
    int rc = 0;

    if (stat(s, &st)) {

	(void)unlink(s);
	if ((f = fopen(s, "w")) != NULL) {
	    if (fsync(fileno(f))) rc = -1;
	    if (fclose(f)) rc = -1;
	} else {

	    rc = -1;
	}
    } else {
	buf.actime = (now < st.st_atime) ? st.st_atime : now;

	buf.modtime = st.st_mtime;
	if (utime(s, &buf)) {
	    rc = -1;
	}
    }
    if (rc)
	ln_log(LNLOG_SERR, LNLOG_CTOP, "cannot update or create %s: %m", s);
    free(s);
    return rc;
}

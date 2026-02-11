seen_delete_user(const char *user)
{
    char *fname = seen_getpath(user);
    int r = 0;

    if (SEEN_DEBUG) {
	syslog(LOG_DEBUG, "seen_db: seen_delete_user(%s)",
	       user);
    }

    if (unlink(fname) && errno != ENOENT) {
	syslog(LOG_ERR, "error unlinking %s: %m", fname);
	r = IMAP_IOERROR;
    }

    free(fname);
    return r;
}

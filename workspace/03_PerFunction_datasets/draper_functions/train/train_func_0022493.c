logfileOpen(const char *path, size_t bufsz, int fatal_flag)
{
    Logfile *lf;
    const char *patharg;
    int ret;

    debug(50, 1) ("logfileOpen: opening log %s\n", path);

    CBDATA_INIT_TYPE(Logfile);
    lf = cbdataAlloc(Logfile);
    xstrncpy(lf->path, path, MAXPATHLEN);
    patharg = path;


    if (strncmp(path, "stdio:", 6) == 0) {
	patharg = path + 6;
	ret = logfile_mod_stdio_open(lf, patharg, bufsz, fatal_flag);
    } else if (strncmp(path, "daemon:", 7) == 0) {
	patharg = path + 7;
	ret = logfile_mod_daemon_open(lf, patharg, bufsz, fatal_flag);
    } else if (strncmp(path, "udp:", 4) == 0) {
	patharg = path + 4;
	ret = logfile_mod_udp_open(lf, patharg, bufsz, fatal_flag);
#if HAVE_SYSLOG
    } else if (strncmp(path, "syslog:", 7) == 0) {
	patharg = path + 7;
	ret = logfile_mod_syslog_open(lf, patharg, bufsz, fatal_flag);
#endif
    } else {
	ret = logfile_mod_stdio_open(lf, patharg, bufsz, fatal_flag);
    }
    if (!ret) {
	if (fatal_flag)
	    fatalf("logfileOpen: path %s: couldn't open!\n", path);
	else
	    debug(50, 1) ("logfileOpen: path %s: couldn't open!\n", path);
	lf->f_close(lf);
	cbdataFree(lf);
	return NULL;
    }
    assert(lf->data != NULL);

    if (fatal_flag)
	lf->flags.fatal = 1;
    lf->sequence_number = 0;
    return lf;
}

NsCreatePidFile(char *procname)
{
    int	  fd, n;
    char  buf[10];
    char *file = GetFile(procname);

    fd = open(file, O_WRONLY|O_TRUNC|O_CREAT, 0644);
    if (fd < 0) {
    	Ns_Log(Error, "pidfile: failed to open pid file '%s': '%s'",
	       file, strerror(errno));
    } else {
	sprintf(buf, "%d\n", nsconf.pid);
	n = strlen(buf);
	if (write(fd, buf, (size_t)n) != n) {
	    Ns_Log(Error, "pidfile: write() failed: '%s'", strerror(errno));
	}
        close(fd);
    }
}

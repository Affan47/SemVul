MXCommand(char const *sockname,
	  char const *cmd,
	  char *buf,
	  int len)
{
    int fd;
    struct sockaddr_un addr;
    int nread;
    int n;

    fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (fd < 0) {
	syslog(LOG_ERR, "MXCommand: socket: %m");
	return MD_TEMPFAIL;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strncpy(addr.sun_path, sockname, sizeof(addr.sun_path) - 1);

    if (connect(fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
	syslog(LOG_ERR, "MXCommand: connect: %m: Is multiplexor running?");
	close(fd);
	return MD_TEMPFAIL;
    }

    n = writestr(fd, cmd);
    if (n < 0) {
	syslog(LOG_ERR, "MXCommand: write: %m: Is multiplexor running?");
	close(fd);
	return MD_TEMPFAIL;
    }


    nread = readn(fd, buf, len-1);
    if (nread < 0) {
	syslog(LOG_ERR, "MXCommand: read: %m: Is multiplexor running?");
	close(fd);
	return MD_TEMPFAIL;
    }
    buf[nread] = 0;

    if (nread == len-1) {
	char slop[SMALLBUF];
	if (readn(fd, slop, SMALLBUF) > 0) {
	    syslog(LOG_WARNING, "MXCommand: Overlong reply from multiplexor was truncated!");

	    while (readn(fd, slop, SMALLBUF) > 0);
	}
    }
    close(fd);
    return 0;
}

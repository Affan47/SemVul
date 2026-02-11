_sfdup(reg int fd, reg int newfd)
#else
static int _sfdup(fd, newfd)
reg int fd;
reg int newfd;
#endif
{
    reg int dupfd;

#ifdef F_DUPFD
    while ((dupfd = fcntl(fd, F_DUPFD, newfd)) < 0 && errno == EINTR)
	errno = 0;
    return dupfd;

#else
    if ((dupfd = dup(fd)) < 0 || dupfd >= newfd)
	return dupfd;


    newfd = _sfdup(fd, newfd);


    CLOSE(dupfd);

    return newfd;
#endif
}

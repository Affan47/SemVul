ICCopen(void)
{
    int mask, oerrno, fd;
#ifdef HAVE_UNIX_DOMAIN_SOCKETS
    int size = 65535;
#endif

    if (innconf == NULL) {
	if (!innconf_read(NULL)) {
	    ICCfailure = "innconf";
	    return -1;
	}
    }


    if (ICCsockname == NULL)
	ICCsockname = concatpath(innconf->pathrun, INN_PATH_TEMPSOCK);
    fd = mkstemp(ICCsockname);
    if (fd < 0) {
        ICCfailure = "mkstemp";
        return -1;
    }
    close(fd);
    if (unlink(ICCsockname) < 0 && errno != ENOENT) {
	ICCfailure = "unlink";
	return -1;
    }

#ifdef HAVE_UNIX_DOMAIN_SOCKETS


    if ((ICCfd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
	ICCfailure = "socket";
	return -1;
    }


    setsockopt(ICCfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));

    memset(&ICCclient, 0, sizeof ICCclient);
    ICCclient.sun_family = AF_UNIX;
    strlcpy(ICCclient.sun_path, ICCsockname, sizeof(ICCclient.sun_path));
    mask = umask(0);
    if (bind(ICCfd, (struct sockaddr *) &ICCclient, SUN_LEN(&ICCclient)) < 0) {
	oerrno = errno;
	umask(mask);
	errno = oerrno;
	ICCfailure = "bind";
	return -1;
    }
    umask(mask);


    memset(&ICCserv, 0, sizeof ICCserv);
    ICCserv.sun_family = AF_UNIX;
    strlcpy(ICCserv.sun_path, innconf->pathrun, sizeof(ICCserv.sun_path));
    strlcat(ICCserv.sun_path, "/", sizeof(ICCserv.sun_path));
    strlcat(ICCserv.sun_path, INN_PATH_NEWSCONTROL, sizeof(ICCserv.sun_path));

#else


    mask = umask(0);
    if (mkfifo(ICCsockname, 0666) < 0) {
	oerrno = errno;
	umask(mask);
	errno = oerrno;
	ICCfailure = "mkfifo";
	return -1;
    }
    umask(mask);
    if ((ICCfd = open(ICCsockname, O_RDWR)) < 0) {
	ICCfailure = "open";
	return -1;
    }
#endif

    ICCfailure = NULL;
    return 0;
}

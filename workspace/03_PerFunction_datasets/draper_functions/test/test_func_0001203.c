RChandoff(fd, h)
    int		fd;
    HANDOFF	h;
{
    STRING	argv[6];
    char	buff[SMBUF];
    int		i;

#if	defined(SOL_SOCKET) && defined(SO_KEEPALIVE)

    i = 1;
    if (setsockopt(fd, SOL_SOCKET,  SO_KEEPALIVE, (char *)&i, sizeof i) < 0)
        syslog(L_ERROR, "fd %d cant setsockopt(KEEPALIVE) %m", fd);
#endif

    if (SetNonBlocking(fd, FALSE) < 0)
	syslog(L_ERROR, "%s cant nonblock %d in RChandoff %m", LogName, fd);
    switch (h) {
    default:
	syslog(L_ERROR, "%s internal RChandoff %d type %d", LogName, fd, h);

    case HOnnrpd:	argv[0] = RCnnrpd;	break;
    case HOnnrqd:	argv[0] = RCnnrqd;	break;
    case HOnntpd:	argv[0] = RCnntpd;	break;
    }
    argv[1] = "-s                                                ";
    i = 2;
    if (NNRPReason) {
	(void)sprintf(buff, "-r%s", NNRPReason);
	argv[i++] = buff;
    }
    if (NNRPTracing)
	argv[i++] = "-t";
    if (RCslaveflag)
	argv[i++] = RCslaveflag;
    argv[i] = NULL;


    (void)Spawn(fd, fd, fd, argv);
}

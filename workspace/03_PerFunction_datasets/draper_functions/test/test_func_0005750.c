CCgo(char *av[])
{
    static char	YES[] = "y";
    char	*p;

    p = av[0];
    if (Reservation && strcmp(p, Reservation) == 0) {
	free(Reservation);
	Reservation = NULL;
    }
    if (RejectReason && strcmp(p, RejectReason) == 0) {
	free(RejectReason);
	RejectReason = NULL;
    }

    if (Mode == OMrunning)
	return "1 Already running";
    if (*p && strcmp(p, ModeReason) != 0)
	return "1 Wrong reason";

#if defined(DO_PERL)
    PLmode(Mode, OMrunning, p);
#endif
#if defined(DO_PYTHON)
    PYmode(Mode, OMrunning, p);
#endif

    free(ModeReason);
    ModeReason = NULL;
    Mode = OMrunning;
    ThrottledbyIOError = false;

    if (NNRPReason != NULL && !innconf->readerswhenstopped) {
	av[0] = YES;
	av[1] = p;
	CCreaders(av);
    }
    if (ErrorCount < 0)
	ErrorCount = IO_ERROR_COUNT;
    InndHisOpen();
    syslog(L_NOTICE, "%s running", LogName);
    if (ICDneedsetup)
	ICDsetup(true);
    SCHANwakeup(&Mode);
    return NULL;
}

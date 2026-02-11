DUL_associationWaiting(DUL_NETWORKKEY * callerNet, int timeout)
{
    PRIVATE_NETWORKKEY *net;
    int                 s;
    OFBool             assocWaiting = OFFalse;
    struct timeval      t;
    fd_set              fdset;
    int                 nfound;

    if (callerNet == NULL)
        return OFFalse;

    net = (PRIVATE_NETWORKKEY*)callerNet;

    s = net->networkSpecific.TCP.listenSocket;

    FD_ZERO(&fdset);
#ifdef __MINGW32__

    FD_SET((unsigned int) s, &fdset);
#else
    FD_SET(s, &fdset);
#endif

    t.tv_sec = timeout;
    t.tv_usec = 0;
#ifdef HAVE_INTP_SELECT
    nfound = select(s + 1, (int *)(&fdset), NULL, NULL, &t);
#else
    nfound = select(s + 1, &fdset, NULL, NULL, &t);
#endif
    if (nfound <= 0) assocWaiting = OFFalse;
    else
    {
        if (FD_ISSET(s, &fdset))
            assocWaiting = OFTrue;
        else
            assocWaiting = OFFalse;
    }

    return assocWaiting;
}

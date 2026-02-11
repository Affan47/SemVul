SockAccept(SOCKET lsock, Driver *drvPtr)
{
    Sock *sockPtr = drvPtr->freeSockPtr;
    int slen;


    slen = sizeof(struct sockaddr_in);
    sockPtr->sock = Ns_SockAccept(lsock,
            (struct sockaddr *) &sockPtr->sa, &slen);
    if (sockPtr->sock == INVALID_SOCKET) {
	return NULL;
    }
    sockPtr->id = drvPtr->nextid++;
    sockPtr->drvPtr = drvPtr;
    sockPtr->state = SOCK_READWAIT;
    sockPtr->arg = NULL;
    sockPtr->connPtr = NULL;


    Ns_SockSetNonBlocking(sockPtr->sock);


    if (drvPtr->sndbuf > 0) {
	setsockopt(sockPtr->sock, SOL_SOCKET, SO_SNDBUF,
	    (char *) &drvPtr->sndbuf, sizeof(drvPtr->sndbuf));
    }
    if (drvPtr->rcvbuf > 0) {
	setsockopt(sockPtr->sock, SOL_SOCKET, SO_RCVBUF,
	    (char *) &drvPtr->rcvbuf, sizeof(drvPtr->rcvbuf));
    }
    ++drvPtr->nactive;
    drvPtr->freeSockPtr = sockPtr->nextPtr;
    sockPtr->nextPtr = NULL;
    return sockPtr;
}

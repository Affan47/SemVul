FreeConn(Conn *connPtr)
{
    size_t zlen;
    Ns_Conn *conn = (Ns_Conn *) connPtr;


    NsClsCleanup(connPtr);


    if (conn->request != NULL) {
    	Ns_FreeRequest(conn->request);
    }
    if (connPtr->map != NULL) {
	NsUnMap(connPtr->map, connPtr->maparg);
    }
    if (connPtr->tfd != -1) {
        Ns_ReleaseTemp(connPtr->tfd);
    }
    if (connPtr->authUser != NULL) {
        ns_free(connPtr->authUser);
    }
    Ns_SetFree(connPtr->headers);


    Ns_DStringTrunc(&connPtr->ibuf, 0);
    zlen = (size_t) ((char *) &connPtr->ibuf - (char *) connPtr);
    memset(connPtr, 0, zlen);

    Ns_MutexLock(&connlock);
    connPtr->nextPtr = firstConnPtr;
    firstConnPtr = connPtr;
    Ns_MutexUnlock(&connlock);
}

Ns_ConnReadHeaders(Ns_Conn *conn, Ns_Set *set, int *nreadPtr)
{
    Ns_DString      ds;
    Conn           *connPtr = (Conn *) conn;
    NsServer	   *servPtr = connPtr->servPtr;
    int             status, nread, nline, maxhdr;

    Ns_DStringInit(&ds);
    nread = 0;
    maxhdr = connPtr->drvPtr->maxinput;
    status = NS_OK;
    while (nread < maxhdr && status == NS_OK) {
        Ns_DStringTrunc(&ds, 0);
        status = Ns_ConnReadLine(conn, &ds, &nline);
        if (status == NS_OK) {
            nread += nline;
            if (nread > maxhdr) {
                status = NS_ERROR;
            } else {
                if (ds.string[0] == '\0') {
                    break;
                }
                status = Ns_ParseHeader(set, ds.string, servPtr->opts.hdrcase);
            }
        }
    }
    if (nreadPtr != NULL) {
	*nreadPtr = nread;
    }
    Ns_DStringFree(&ds);
    return status;
}

forgetConn(connInfoType *conn)
{
    fdInfoType *infos[5], *info;
    register int i=0;
    infos[i++]=conn->client;
    if (conn->client->peer)
	infos[i++]=conn->client->peer;
    if (conn->udp) {
	infos[i++]=conn->udp;
	if (conn->udp->peer)
	    infos[i++]=conn->udp->peer;
    }
    infos[i]=NULL;
    for (i=0;infos[i]; i++) {
	forgetInfo(infos[i]);
    }
    conn->startTime=0;
    conn->flags &= ~CO_IN_USE;
    conn->client=(fdInfoType*)freeConn;
    freeConn=conn;
}

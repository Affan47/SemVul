SSL_SetSockPeerID(PRFileDesc *fd, const char *peerID)
{
    sslSocket *ss;

    ss = ssl_FindSocket(fd);
    if (!ss) {
        SSL_DBG(("%d: SSL[%d]: bad socket in SSL_SetSockPeerID",
                 SSL_GETPID(), fd));
        return SECFailure;
    }

    if (ss->peerID) {
        PORT_Free(ss->peerID);
        ss->peerID = NULL;
    }
    if (peerID)
        ss->peerID = PORT_Strdup(peerID);
    return (ss->peerID || !peerID) ? SECSuccess : SECFailure;
}

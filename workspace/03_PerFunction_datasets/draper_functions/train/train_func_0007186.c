SSL_ForceHandshake(PRFileDesc *fd)
{
    sslSocket *ss;
    SECStatus  rv = SECFailure;

    ss = ssl_FindSocket(fd);
    if (!ss) {
	SSL_DBG(("%d: SSL[%d]: bad socket in ForceHandshake",
		 SSL_GETPID(), fd));
	return rv;
    }


    if (!ss->opt.useSecurity)
    	return SECSuccess;

    if (!ssl_SocketIsBlocking(ss)) {
	ssl_GetXmitBufLock(ss);
	if (ss->pendingBuf.len != 0) {
	    int sent = ssl_SendSavedWriteData(ss);
	    if ((sent < 0) && (PORT_GetError() != PR_WOULD_BLOCK_ERROR)) {
		ssl_ReleaseXmitBufLock(ss);
		return SECFailure;
	    }
	}
	ssl_ReleaseXmitBufLock(ss);
    }

    ssl_Get1stHandshakeLock(ss);

    if (ss->version >= SSL_LIBRARY_VERSION_3_0) {
	int gatherResult;

    	ssl_GetRecvBufLock(ss);
	gatherResult = ssl3_GatherCompleteHandshake(ss, 0);
	ssl_ReleaseRecvBufLock(ss);
	if (gatherResult > 0) {
	    rv = SECSuccess;
	} else if (gatherResult == 0) {
	    PORT_SetError(PR_END_OF_FILE_ERROR);
	} else if (gatherResult == SECWouldBlock) {
	    PORT_SetError(PR_WOULD_BLOCK_ERROR);
	}
    } else if (!ss->firstHsDone) {
	rv = ssl_Do1stHandshake(ss);
    } else {


    	rv = SECSuccess;
    }

    ssl_Release1stHandshakeLock(ss);

    return rv;
}

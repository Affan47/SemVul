ssl2_HandleV3HandshakeRecord(sslSocket *ss)
{
    SECStatus           rv;

    PORT_Assert( ss->opt.noLocks || ssl_HaveRecvBufLock(ss) );
    PORT_Assert( ss->opt.noLocks || ssl_Have1stHandshakeLock(ss) );


    ss->gs.remainder         = 2;
    ss->gs.count             = 0;


    ss->nextHandshake     = 0;
    ss->securityHandshake = 0;


    rv = ssl3_NegotiateVersion(ss, SSL_LIBRARY_VERSION_MAX_SUPPORTED,
			       PR_TRUE);
    if (rv != SECSuccess) {
	return rv;
    }

    ss->sec.send         = ssl3_SendApplicationData;

    return SECSuccess;
}

ssl2_GetSendBuffer(sslSocket *ss, unsigned int len)
{
    SECStatus rv = SECSuccess;

    PORT_Assert(ss->opt.noLocks || ssl_HaveXmitBufLock(ss));

    if (len < 128) {
	len = 128;
    }
    if (len > ss->sec.ci.sendBuf.space) {
	rv = sslBuffer_Grow(&ss->sec.ci.sendBuf, len);
	if (rv != SECSuccess) {
	    SSL_DBG(("%d: SSL[%d]: ssl2_GetSendBuffer failed, tried to get %d bytes",
		     SSL_GETPID(), ss->fd, len));
	    rv = SECFailure;
	}
    }
    return rv;
}

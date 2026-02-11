ssl3_FlushHandshakeMessages(sslSocket *ss, PRInt32 flags)
{
    static const PRInt32 allowedFlags = ssl_SEND_FLAG_FORCE_INTO_BUFFER |
                                        ssl_SEND_FLAG_CAP_RECORD_VERSION;
    PRInt32 rv = SECSuccess;

    PORT_Assert( ss->opt.noLocks || ssl_HaveSSL3HandshakeLock(ss));
    PORT_Assert( ss->opt.noLocks || ssl_HaveXmitBufLock(ss) );

    if (!ss->sec.ci.sendBuf.buf || !ss->sec.ci.sendBuf.len)
	return rv;


    PORT_Assert(!(flags & ~allowedFlags));
    if ((flags & ~allowedFlags) != 0) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	rv = SECFailure;
    } else {
	rv = ssl3_SendRecord(ss, 0, content_handshake, ss->sec.ci.sendBuf.buf,
			     ss->sec.ci.sendBuf.len, flags);
    }
    if (rv < 0) {
    	int err = PORT_GetError();
	PORT_Assert(err != PR_WOULD_BLOCK_ERROR);
	if (err == PR_WOULD_BLOCK_ERROR) {
	    PORT_SetError(SEC_ERROR_LIBRARY_FAILURE);
	}
    } else if (rv < ss->sec.ci.sendBuf.len) {

	PORT_Assert(rv >= ss->sec.ci.sendBuf.len);
	PORT_SetError(SEC_ERROR_LIBRARY_FAILURE);
	rv = SECFailure;
    } else {
	rv = SECSuccess;
    }


    ss->sec.ci.sendBuf.len = 0;
    return rv;
}

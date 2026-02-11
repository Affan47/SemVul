dtls_FlushHandshakeMessages(sslSocket *ss, PRInt32 flags)
{
    SECStatus rv = SECSuccess;

    PORT_Assert(ss->opt.noLocks || ssl_HaveSSL3HandshakeLock(ss));
    PORT_Assert(ss->opt.noLocks || ssl_HaveXmitBufLock(ss));

    rv = dtls_StageHandshakeMessage(ss);
    if (rv != SECSuccess)
        return rv;

    if (!(flags & ssl_SEND_FLAG_FORCE_INTO_BUFFER)) {
        rv = dtls_TransmitMessageFlight(ss);
        if (rv != SECSuccess)
            return rv;

	if (!(flags & ssl_SEND_FLAG_NO_RETRANSMIT)) {
	    ss->ssl3.hs.rtRetries = 0;
	    rv = dtls_StartTimer(ss, dtls_RetransmitTimerExpiredCb);
	}
    }

    return rv;
}

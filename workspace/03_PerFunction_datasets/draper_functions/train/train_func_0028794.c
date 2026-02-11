SSL_ReHandshake(PRFileDesc *fd, PRBool flushCache)
{
    sslSocket *ss;
    SECStatus  rv;

    ss = ssl_FindSocket(fd);
    if (!ss) {
	SSL_DBG(("%d: SSL[%d]: bad socket in RedoHandshake", SSL_GETPID(), fd));
	return SECFailure;
    }

    if (!ss->opt.useSecurity)
	return SECSuccess;

    ssl_Get1stHandshakeLock(ss);


    if (ss->version < SSL_LIBRARY_VERSION_3_0) {
	PORT_SetError(SSL_ERROR_FEATURE_NOT_SUPPORTED_FOR_SSL2);
	rv = SECFailure;
    } else {
	ssl_GetSSL3HandshakeLock(ss);
	rv = ssl3_RedoHandshake(ss, flushCache);
	ssl_ReleaseSSL3HandshakeLock(ss);
    }

    ssl_Release1stHandshakeLock(ss);

    return rv;
}

SSL_SetURL(PRFileDesc *fd, const char *url)
{
    sslSocket *   ss = ssl_FindSocket(fd);
    SECStatus     rv = SECSuccess;

    if (!ss) {
	SSL_DBG(("%d: SSL[%d]: bad socket in SSLSetURL",
		 SSL_GETPID(), fd));
	return SECFailure;
    }
    ssl_Get1stHandshakeLock(ss);
    ssl_GetSSL3HandshakeLock(ss);

    if ( ss->url ) {
	PORT_Free((void *)ss->url);
    }

    ss->url = (const char *)PORT_Strdup(url);
    if ( ss->url == NULL ) {
	rv = SECFailure;
    }

    ssl_ReleaseSSL3HandshakeLock(ss);
    ssl_Release1stHandshakeLock(ss);

    return rv;
}

SSL_CipherPrefSet(PRFileDesc *fd, PRInt32 which, PRBool enabled)
{
    SECStatus rv;
    sslSocket *ss = ssl_FindSocket(fd);

    if (!ss) {
	SSL_DBG(("%d: SSL[%d]: bad socket in CipherPrefSet", SSL_GETPID(), fd));
	return SECFailure;
    }
    if (ssl_IsRemovedCipherSuite(which))
    	return SECSuccess;
    if (enabled && ss->opt.noStepDown && SSL_IsExportCipherSuite(which)) {
    	PORT_SetError(SEC_ERROR_INVALID_ALGORITHM);
	return SECFailure;
    }
    if (SSL_IS_SSL2_CIPHER(which)) {
	rv = ssl2_CipherPrefSet(ss, which, enabled);
    } else {
	rv = ssl3_CipherPrefSet(ss, (ssl3CipherSuite)which, enabled);
    }
    return rv;
}

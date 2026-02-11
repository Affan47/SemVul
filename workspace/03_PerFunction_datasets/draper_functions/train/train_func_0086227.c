SSL_RecommendedCanFalseStart(PRFileDesc *fd, PRBool *canFalseStart)
{
    sslSocket *ss;

    *canFalseStart = PR_FALSE;
    ss = ssl_FindSocket(fd);
    if (!ss) {
	SSL_DBG(("%d: SSL[%d]: bad socket in SSL_RecommendedCanFalseStart",
		 SSL_GETPID(), fd));
	return SECFailure;
    }

    if (!ss->ssl3.initialized) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return SECFailure;
    }

    if (ss->version < SSL_LIBRARY_VERSION_3_0) {
	PORT_SetError(SSL_ERROR_FEATURE_NOT_SUPPORTED_FOR_SSL2);
	return SECFailure;
    }


    *canFalseStart = ss->ssl3.hs.kea_def->kea == kea_dhe_dss ||
		     ss->ssl3.hs.kea_def->kea == kea_dhe_rsa ||
		     ss->ssl3.hs.kea_def->kea == kea_ecdhe_ecdsa ||
		     ss->ssl3.hs.kea_def->kea == kea_ecdhe_rsa;

    return SECSuccess;
}

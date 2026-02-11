SSL_LocalCertificate(PRFileDesc *fd)
{
    sslSocket *ss;

    ss = ssl_FindSocket(fd);
    if (!ss) {
	SSL_DBG(("%d: SSL[%d]: bad socket in PeerCertificate",
		 SSL_GETPID(), fd));
	return NULL;
    }
    if (ss->opt.useSecurity) {
    	if (ss->sec.localCert) {
	    return CERT_DupCertificate(ss->sec.localCert);
	}
	if (ss->sec.ci.sid && ss->sec.ci.sid->localCert) {
	    return CERT_DupCertificate(ss->sec.ci.sid->localCert);
	}
    }
    return NULL;
}

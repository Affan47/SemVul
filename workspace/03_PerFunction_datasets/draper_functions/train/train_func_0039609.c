SSL_PeerCertificate(PRFileDesc *fd)
{
    sslSocket *ss;

    ss = ssl_FindSocket(fd);
    if (!ss) {
	SSL_DBG(("%d: SSL[%d]: bad socket in PeerCertificate",
		 SSL_GETPID(), fd));
	return 0;
    }
    if (ss->opt.useSecurity && ss->sec.peerCert) {
	return CERT_DupCertificate(ss->sec.peerCert);
    }
    return 0;
}

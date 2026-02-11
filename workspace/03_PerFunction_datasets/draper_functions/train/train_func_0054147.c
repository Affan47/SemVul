nss_var_lookup_nss_cert_verify(apr_pool_t *p, conn_rec *c)
{
    SSLConnRec *sslconn = myConnConfig(c);
    char *result;
    PRFileDesc *ssl;
    SECStatus rv;
    CERTCertificate *xs;
    void *pinArg;

    result = NULL;
    ssl   = sslconn->ssl;
    xs    = SSL_PeerCertificate(ssl);
    pinArg = SSL_RevealPinArg(sslconn->ssl);

    if (xs == NULL)
        result = "NONE";
    else {
        rv = CERT_VerifyCertNow(CERT_GetDefaultCertDB(),
                                xs,
                                PR_TRUE,
                                certUsageSSLClient,
                                pinArg);

        if (rv == SECSuccess)
            result = "SUCCESS";
        else
            result = apr_psprintf(p, "FAILED");
    }

    if (xs)
        CERT_DestroyCertificate(xs);

    return result;
}

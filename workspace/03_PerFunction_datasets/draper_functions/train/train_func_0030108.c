CERT_DecodeCertFromPackage(char *certbuf, int certlen)
{
    collect_args collectArgs;
    SECStatus rv;
    CERTCertificate *cert = NULL;

    collectArgs.arena = PORT_NewArena(DER_DEFAULT_CHUNKSIZE);

    rv = CERT_DecodeCertPackage(certbuf, certlen, collect_certs,
				(void *)&collectArgs);
    if ( rv == SECSuccess ) {
	cert = CERT_NewTempCertificate(CERT_GetDefaultCertDB(),
	                               &collectArgs.cert, NULL,
	                               PR_FALSE, PR_TRUE);
    }

    PORT_FreeArena(collectArgs.arena, PR_FALSE);

    return(cert);
}

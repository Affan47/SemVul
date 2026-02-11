cert_ComputeTrustOverrides(CERTCertificate *cert, unsigned int cType)
{
    CERTCertTrust trust;
    SECStatus rv = SECFailure;

    rv = CERT_GetCertTrust(cert, &trust);

    if (rv == SECSuccess && (trust.sslFlags |
		  trust.emailFlags |
		  trust.objectSigningFlags)) {

	if (trust.sslFlags & (CERTDB_TERMINAL_RECORD|CERTDB_TRUSTED))
	    cType |= NS_CERT_TYPE_SSL_SERVER|NS_CERT_TYPE_SSL_CLIENT;
	if (trust.sslFlags & (CERTDB_VALID_CA|CERTDB_TRUSTED_CA))
	    cType |= NS_CERT_TYPE_SSL_CA;
#if defined(CERTDB_NOT_TRUSTED)
	if (trust.sslFlags & CERTDB_NOT_TRUSTED)
	    cType &= ~(NS_CERT_TYPE_SSL_SERVER|NS_CERT_TYPE_SSL_CLIENT|
	               NS_CERT_TYPE_SSL_CA);
#endif
	if (trust.emailFlags & (CERTDB_TERMINAL_RECORD|CERTDB_TRUSTED))
	    cType |= NS_CERT_TYPE_EMAIL;
	if (trust.emailFlags & (CERTDB_VALID_CA|CERTDB_TRUSTED_CA))
	    cType |= NS_CERT_TYPE_EMAIL_CA;
#if defined(CERTDB_NOT_TRUSTED)
	if (trust.emailFlags & CERTDB_NOT_TRUSTED)
	    cType &= ~(NS_CERT_TYPE_EMAIL|NS_CERT_TYPE_EMAIL_CA);
#endif
	if (trust.objectSigningFlags & (CERTDB_TERMINAL_RECORD|CERTDB_TRUSTED))
	    cType |= NS_CERT_TYPE_OBJECT_SIGNING;
	if (trust.objectSigningFlags & (CERTDB_VALID_CA|CERTDB_TRUSTED_CA))
	    cType |= NS_CERT_TYPE_OBJECT_SIGNING_CA;
#if defined(CERTDB_NOT_TRUSTED)
	if (trust.objectSigningFlags & CERTDB_NOT_TRUSTED)
	    cType &= ~(NS_CERT_TYPE_OBJECT_SIGNING|
	               NS_CERT_TYPE_OBJECT_SIGNING_CA);
#endif
    }
    return cType;
}

CERT_IsCACert(CERTCertificate *cert, unsigned int *rettype)
{
    unsigned int cType = cert->nsCertType;
    PRBool ret = PR_FALSE;

    if (cType & (NS_CERT_TYPE_SSL_CA | NS_CERT_TYPE_EMAIL_CA |
                NS_CERT_TYPE_OBJECT_SIGNING_CA)) {
        ret = PR_TRUE;
    } else {
	SECStatus rv;
	CERTBasicConstraints constraints;

	rv = CERT_FindBasicConstraintExten(cert, &constraints);
	if (rv == SECSuccess && constraints.isCA) {
	    ret = PR_TRUE;
	    cType |= (NS_CERT_TYPE_SSL_CA | NS_CERT_TYPE_EMAIL_CA);
	}
    }


    if (!ret &&
        (cert->isRoot && cert_Version(cert) < SEC_CERTIFICATE_VERSION_3)) {
	ret = PR_TRUE;
	cType |= (NS_CERT_TYPE_SSL_CA | NS_CERT_TYPE_EMAIL_CA);
    }

    cType = cert_ComputeTrustOverrides(cert, cType);
    ret = (cType & (NS_CERT_TYPE_SSL_CA | NS_CERT_TYPE_EMAIL_CA |
                    NS_CERT_TYPE_OBJECT_SIGNING_CA)) ? PR_TRUE : PR_FALSE;

    if (rettype != NULL) {
	*rettype = cType;
    }
    return ret;
}

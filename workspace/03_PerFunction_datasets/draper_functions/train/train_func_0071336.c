xmlSecNssX509CertBase64DerWrite(CERTCertificate* cert, int base64LineWrap) {
    xmlChar *res = NULL;
    xmlSecByte *p = NULL;
    long size;

    xmlSecAssert2(cert != NULL, NULL);

    p = cert->derCert.data;
    size = cert->derCert.len;
    if((size <= 0) || (p == NULL)){
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "cert->derCert",
		    XMLSEC_ERRORS_R_CRYPTO_FAILED,
		    "error code=%d", PORT_GetError());
	return(NULL);
    }

    res = xmlSecBase64Encode(p, size, base64LineWrap);
    if(res == NULL) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecBase64Encode",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(NULL);
    }

    return(res);
}

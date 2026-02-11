xmlSecNssX509CertificateNodeRead(xmlSecKeyDataPtr data, xmlNodePtr node, xmlSecKeyInfoCtxPtr keyInfoCtx) {
    xmlChar *content;
    CERTCertificate* cert;
    int ret;

    xmlSecAssert2(xmlSecKeyDataCheckId(data, xmlSecNssKeyDataX509Id), -1);
    xmlSecAssert2(node != NULL, -1);
    xmlSecAssert2(keyInfoCtx != NULL, -1);

    content = xmlNodeGetContent(node);
    if((content == NULL) || (xmlSecIsEmptyString(content) == 1)) {
	if(content != NULL) {
	    xmlFree(content);
	}
	if((keyInfoCtx->flags & XMLSEC_KEYINFO_FLAGS_STOP_ON_EMPTY_NODE) != 0) {
	    xmlSecError(XMLSEC_ERRORS_HERE,
			xmlSecErrorsSafeString(xmlSecKeyDataGetName(data)),
			xmlSecErrorsSafeString(xmlSecNodeGetName(node)),
			XMLSEC_ERRORS_R_INVALID_NODE_CONTENT,
			XMLSEC_ERRORS_NO_MESSAGE);
	    return(-1);
	}
	return(0);
    }

    cert = xmlSecNssX509CertBase64DerRead(content);
    if(cert == NULL) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecKeyDataGetName(data)),
		    "xmlSecNssX509CertBase64DerRead",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	xmlFree(content);
	return(-1);
    }

    ret = xmlSecNssKeyDataX509AdoptCert(data, cert);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    xmlSecErrorsSafeString(xmlSecKeyDataGetName(data)),
		    "xmlSecNssKeyDataX509AdoptCert",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	CERT_DestroyCertificate(cert);
	xmlFree(content);
	return(-1);
    }

    xmlFree(content);
    return(0);
}

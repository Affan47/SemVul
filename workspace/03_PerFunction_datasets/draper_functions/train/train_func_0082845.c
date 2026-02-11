xmlSecOpenSSLKeyDataRawX509CertBinRead(xmlSecKeyDataId id, xmlSecKeyPtr key,
                                    const xmlSecByte* buf, xmlSecSize bufSize,
                                    xmlSecKeyInfoCtxPtr keyInfoCtx) {
    xmlSecKeyDataPtr data;
    X509* cert;
    int ret;

    xmlSecAssert2(id == xmlSecOpenSSLKeyDataRawX509CertId, -1);
    xmlSecAssert2(key != NULL, -1);
    xmlSecAssert2(buf != NULL, -1);
    xmlSecAssert2(bufSize > 0, -1);
    xmlSecAssert2(keyInfoCtx != NULL, -1);

    cert = xmlSecOpenSSLX509CertDerRead(buf, bufSize);
    if(cert == NULL) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecOpenSSLX509CertDerRead",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }

    data = xmlSecKeyEnsureData(key, xmlSecOpenSSLKeyDataX509Id);
    if(data == NULL) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(id)),
                    "xmlSecKeyEnsureData",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        X509_free(cert);
        return(-1);
    }

    ret = xmlSecOpenSSLKeyDataX509AdoptCert(data, cert);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(id)),
                    "xmlSecOpenSSLKeyDataX509AdoptCert",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        X509_free(cert);
        return(-1);
    }

    ret = xmlSecOpenSSLKeyDataX509VerifyAndExtractKey(data, key, keyInfoCtx);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecKeyDataKlassGetName(id)),
                    "xmlSecOpenSSLKeyDataX509VerifyAndExtractKey",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }
    return(0);
}

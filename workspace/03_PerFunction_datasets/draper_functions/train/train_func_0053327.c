xmlSecOpenSSLNodeSetBNValue(xmlNodePtr cur, const BIGNUM *a, int addLineBreaks) {
    xmlSecBuffer buf;
    xmlSecSize size;
    int ret;

    xmlSecAssert2(a != NULL, -1);
    xmlSecAssert2(cur != NULL, -1);

    ret = xmlSecBufferInitialize(&buf, BN_num_bytes(a) + 1);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecBufferInitialize",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    "size=%d", BN_num_bytes(a) + 1);
        return(-1);
    }

    ret = BN_bn2bin(a, xmlSecBufferGetData(&buf));
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "BN_bn2bin",
                    XMLSEC_ERRORS_R_CRYPTO_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        xmlSecBufferFinalize(&buf);
        return(-1);
    }
    size = ret;

    ret = xmlSecBufferSetSize(&buf, size);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecBufferSetSize",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    "size=%d", size);
        xmlSecBufferFinalize(&buf);
        return(-1);
    }

    if(addLineBreaks) {
        xmlNodeSetContent(cur, xmlSecStringCR);
    } else {
        xmlNodeSetContent(cur, xmlSecStringEmpty);
    }

    ret = xmlSecBufferBase64NodeContentWrite(&buf, cur, xmlSecBase64GetDefaultLineSize());
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecBufferBase64NodeContentWrite",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        xmlSecBufferFinalize(&buf);
        return(-1);
    }

    if(addLineBreaks) {
        xmlNodeAddContent(cur, xmlSecStringCR);
    }

    xmlSecBufferFinalize(&buf);
    return(0);
}

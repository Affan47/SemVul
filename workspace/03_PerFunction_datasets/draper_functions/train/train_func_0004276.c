xmlSecOpenSSLKWAesInitialize(xmlSecTransformPtr transform) {
    xmlSecOpenSSLKWAesCtxPtr ctx;
    int ret;

    xmlSecAssert2(xmlSecOpenSSLKWAesCheckId(transform), -1);
    xmlSecAssert2(xmlSecTransformCheckSize(transform, xmlSecOpenSSLKWAesSize), -1);

    ctx = xmlSecOpenSSLKWAesGetCtx(transform);
    xmlSecAssert2(ctx != NULL, -1);

    if(xmlSecTransformCheckId(transform, xmlSecOpenSSLTransformKWAes128Id)) {
        ctx->keyExpectedSize = XMLSEC_KW_AES128_KEY_SIZE;
    } else if(xmlSecTransformCheckId(transform, xmlSecOpenSSLTransformKWAes192Id)) {
        ctx->keyExpectedSize = XMLSEC_KW_AES192_KEY_SIZE;
    } else if(xmlSecTransformCheckId(transform, xmlSecOpenSSLTransformKWAes256Id)) {
        ctx->keyExpectedSize = XMLSEC_KW_AES256_KEY_SIZE;
    } else {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                    NULL,
                    XMLSEC_ERRORS_R_INVALID_TRANSFORM,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }

    ret = xmlSecBufferInitialize(&(ctx->keyBuffer), 0);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                    "xmlSecOpenSSLKWAesGetKey",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }

    return(0);
}

xmlSecGCryptKWAesInitialize(xmlSecTransformPtr transform) {
    xmlSecGCryptKWAesCtxPtr ctx;
    int ret;

    xmlSecAssert2(xmlSecGCryptKWAesCheckId(transform), -1);
    xmlSecAssert2(xmlSecTransformCheckSize(transform, xmlSecGCryptKWAesSize), -1);

    ctx = xmlSecGCryptKWAesGetCtx(transform);
    xmlSecAssert2(ctx != NULL, -1);

    if(xmlSecTransformCheckId(transform, xmlSecGCryptTransformKWAes128Id)) {
        ctx->cipher             = GCRY_CIPHER_AES128;
        ctx->keyExpectedSize    = XMLSEC_KW_AES128_KEY_SIZE;
    } else if(xmlSecTransformCheckId(transform, xmlSecGCryptTransformKWAes192Id)) {
        ctx->cipher             = GCRY_CIPHER_AES192;
        ctx->keyExpectedSize    = XMLSEC_KW_AES192_KEY_SIZE;
    } else if(xmlSecTransformCheckId(transform, xmlSecGCryptTransformKWAes256Id)) {
        ctx->cipher             = GCRY_CIPHER_AES256;
        ctx->keyExpectedSize    = XMLSEC_KW_AES256_KEY_SIZE;
    } else {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                    NULL,
                    XMLSEC_ERRORS_R_INVALID_TRANSFORM,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }
    ctx->mode           = GCRY_CIPHER_MODE_CBC;
    ctx->flags          = GCRY_CIPHER_SECURE;
    ctx->blockSize      = gcry_cipher_get_algo_blklen(ctx->cipher);
    xmlSecAssert2(ctx->blockSize > 0, -1);

    ret = xmlSecBufferInitialize(&(ctx->keyBuffer), 0);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(xmlSecTransformGetName(transform)),
                    "xmlSecGCryptKWAesGetKey",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }

    return(0);
}

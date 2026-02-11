xmlSecOpenSSLEvpBlockCipherCtxInit(xmlSecOpenSSLEvpBlockCipherCtxPtr ctx,
                                xmlSecBufferPtr in, xmlSecBufferPtr out,
                                int encrypt,
                                const xmlChar* cipherName,
                                xmlSecTransformCtxPtr transformCtx) {
    int ivLen;
    int ret;

    xmlSecAssert2(ctx != NULL, -1);
    xmlSecAssert2(ctx->cipher != NULL, -1);
    xmlSecAssert2(ctx->keyInitialized != 0, -1);
    xmlSecAssert2(ctx->ctxInitialized == 0, -1);
    xmlSecAssert2(in != NULL, -1);
    xmlSecAssert2(out != NULL, -1);
    xmlSecAssert2(transformCtx != NULL, -1);

    ivLen = EVP_CIPHER_iv_length(ctx->cipher);
    xmlSecAssert2(ivLen > 0, -1);
    xmlSecAssert2((xmlSecSize)ivLen <= sizeof(ctx->iv), -1);

    if(encrypt) {

        ret = RAND_bytes(ctx->iv, ivLen);
        if(ret != 1) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        xmlSecErrorsSafeString(cipherName),
                        "RAND_bytes",
                        XMLSEC_ERRORS_R_CRYPTO_FAILED,
                        "size=%d", ivLen);
            return(-1);
        }


        ret = xmlSecBufferAppend(out, ctx->iv, ivLen);
        if(ret < 0) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        xmlSecErrorsSafeString(cipherName),
                        "xmlSecBufferAppend",
                        XMLSEC_ERRORS_R_XMLSEC_FAILED,
                        "size=%d", ivLen);
            return(-1);
        }

    } else {


        if(xmlSecBufferGetSize(in) < (xmlSecSize)ivLen) {
            return(0);
        }


        xmlSecAssert2(xmlSecBufferGetData(in) != NULL, -1);
        memcpy(ctx->iv, xmlSecBufferGetData(in), ivLen);


        ret = xmlSecBufferRemoveHead(in, ivLen);
        if(ret < 0) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        xmlSecErrorsSafeString(cipherName),
                        "xmlSecBufferRemoveHead",
                        XMLSEC_ERRORS_R_XMLSEC_FAILED,
                        "size=%d", ivLen);
            return(-1);
        }
    }


    ret = EVP_CipherInit(&(ctx->cipherCtx), ctx->cipher, ctx->key, ctx->iv, encrypt);
    if(ret != 1) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    xmlSecErrorsSafeString(cipherName),
                    "EVP_CipherInit",
                    XMLSEC_ERRORS_R_CRYPTO_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }

    ctx->ctxInitialized = 1;


#ifndef XMLSEC_OPENSSL_096
    EVP_CIPHER_CTX_set_padding(&(ctx->cipherCtx), 0);
#endif
    return(0);
}

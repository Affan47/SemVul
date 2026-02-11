xmlSecEncCtxCopyUserPref(xmlSecEncCtxPtr dst, xmlSecEncCtxPtr src) {
    int ret;

    xmlSecAssert2(dst != NULL, -1);
    xmlSecAssert2(src != NULL, -1);

    dst->userData       = src->userData;
    dst->flags          = src->flags;
    dst->flags2         = src->flags2;
    dst->defEncMethodId = src->defEncMethodId;
    dst->mode           = src->mode;

    ret = xmlSecTransformCtxCopyUserPref(&(dst->transformCtx), &(src->transformCtx));
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecTransformCtxCopyUserPref",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }

    ret = xmlSecKeyInfoCtxCopyUserPref(&(dst->keyInfoReadCtx), &(src->keyInfoReadCtx));
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecKeyInfoCtxCopyUserPref",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }

    ret = xmlSecKeyInfoCtxCopyUserPref(&(dst->keyInfoWriteCtx), &(src->keyInfoWriteCtx));
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecKeyInfoCtxCopyUserPref",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }

    return(0);
}

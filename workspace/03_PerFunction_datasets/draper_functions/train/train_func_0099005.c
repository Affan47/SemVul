xmlSecTransformCtxAppend(xmlSecTransformCtxPtr ctx, xmlSecTransformPtr transform) {
    int ret;

    xmlSecAssert2(ctx != NULL, -1);
    xmlSecAssert2(ctx->status == xmlSecTransformStatusNone, -1);
    xmlSecAssert2(xmlSecTransformIsValid(transform), -1);

    if(ctx->last != NULL) {
        ret = xmlSecTransformConnect(ctx->last, transform, ctx);
        if(ret < 0) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        NULL,
                        "xmlSecTransformConnect",
                        XMLSEC_ERRORS_R_XMLSEC_FAILED,
                        "name=%s",
                        xmlSecErrorsSafeString(xmlSecTransformGetName(transform)));
            return(-1);
        }
    } else {
        xmlSecAssert2(ctx->first == NULL, -1);
        ctx->first = transform;
    }
    ctx->last = transform;

    return(0);
}

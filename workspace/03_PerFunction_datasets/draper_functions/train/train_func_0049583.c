xmlSecTransformCtxPrepare(xmlSecTransformCtxPtr ctx, xmlSecTransformDataType inputDataType) {
    xmlSecTransformDataType firstType;
    xmlSecTransformPtr transform;
    int ret;

    xmlSecAssert2(ctx != NULL, -1);
    xmlSecAssert2(ctx->result == NULL, -1);
    xmlSecAssert2(ctx->status == xmlSecTransformStatusNone, -1);


    transform = xmlSecTransformCtxCreateAndAppend(ctx, xmlSecTransformMemBufId);
    if(!xmlSecTransformIsValid(transform)) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecTransformCreate",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    "transform=%s",
                    xmlSecErrorsSafeString(xmlSecTransformKlassGetName(xmlSecTransformMemBufId)));
        return(-1);
    }
    ctx->result = xmlSecTransformMemBufGetBuffer(transform);
    if(ctx->result == NULL) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecTransformMemBufGetBuffer",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    "transform=%s",
                    xmlSecErrorsSafeString(xmlSecTransformKlassGetName(xmlSecTransformMemBufId)));
        return(-1);
    }

    firstType = xmlSecTransformGetDataType(ctx->first, xmlSecTransformModePush, ctx);
    if(((firstType & xmlSecTransformDataTypeBin) == 0) &&
       ((inputDataType & xmlSecTransformDataTypeBin) != 0)) {


        transform = xmlSecTransformCtxCreateAndPrepend(ctx, xmlSecTransformXmlParserId);
        if(transform == NULL) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        NULL,
                        "xmlSecTransformCtxCreateAndPrepend",
                        XMLSEC_ERRORS_R_XMLSEC_FAILED,
                        "transform=%s",
                        xmlSecErrorsSafeString(xmlSecTransformKlassGetName(xmlSecTransformXmlParserId)));
            return(-1);
        }
    } else if(((firstType & xmlSecTransformDataTypeXml) == 0) &&
       ((inputDataType & xmlSecTransformDataTypeXml) != 0)) {


        transform = xmlSecTransformCtxCreateAndPrepend(ctx, xmlSecTransformInclC14NId);
        if(transform == NULL) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        NULL,
                        "xmlSecTransformCtxCreateAndPrepend",
                        XMLSEC_ERRORS_R_XMLSEC_FAILED,
                        "transform=%s",
                        xmlSecErrorsSafeString(xmlSecTransformKlassGetName(xmlSecTransformInclC14NId)));
            return(-1);
        }
    }


    if(ctx->preExecCallback != NULL) {
        ret = (ctx->preExecCallback)(ctx);
        if(ret < 0) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        NULL,
                        "ctx->preExecCallback",
                        XMLSEC_ERRORS_R_XMLSEC_FAILED,
                        XMLSEC_ERRORS_NO_MESSAGE);
            return(-1);
        }
    }

    ctx->status = xmlSecTransformStatusWorking;
    return(0);
}

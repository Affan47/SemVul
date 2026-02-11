xmlSecEncCtxBinaryEncrypt(xmlSecEncCtxPtr encCtx, xmlNodePtr tmpl,
                          const xmlSecByte* data, xmlSecSize dataSize) {
    int ret;

    xmlSecAssert2(encCtx != NULL, -1);
    xmlSecAssert2(encCtx->result == NULL, -1);
    xmlSecAssert2(tmpl != NULL, -1);
    xmlSecAssert2(data != NULL, -1);


    encCtx->operation = xmlSecTransformOperationEncrypt;
    xmlSecAddIDs(tmpl->doc, tmpl, xmlSecEncIds);


    ret = xmlSecEncCtxEncDataNodeRead(encCtx, tmpl);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecEncCtxEncDataNodeRead",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }

    ret = xmlSecTransformCtxBinaryExecute(&(encCtx->transformCtx), data, dataSize);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecTransformCtxBinaryExecute",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    "dataSize=%d",
                    dataSize);
        return(-1);
    }

    encCtx->result = encCtx->transformCtx.result;
    xmlSecAssert2(encCtx->result != NULL, -1);

    ret = xmlSecEncCtxEncDataNodeWrite(encCtx);
    if(ret < 0) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    "xmlSecEncCtxEncDataNodeWrite",
                    XMLSEC_ERRORS_R_XMLSEC_FAILED,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }
    return(0);
}

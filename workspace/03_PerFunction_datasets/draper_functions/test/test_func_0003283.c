xmlSecTransformCtxNodesListRead(xmlSecTransformCtxPtr ctx, xmlNodePtr node, xmlSecTransformUsage usage) {
    xmlSecTransformPtr transform;
    xmlNodePtr cur;
    int ret;

    xmlSecAssert2(ctx != NULL, -1);
    xmlSecAssert2(ctx->status == xmlSecTransformStatusNone, -1);
    xmlSecAssert2(node != NULL, -1);

    cur = xmlSecGetNextElementNode(node->children);
    while((cur != NULL) && xmlSecCheckNodeName(cur, xmlSecNodeTransform, xmlSecDSigNs)) {
        transform = xmlSecTransformNodeRead(cur, usage, ctx);
        if(transform == NULL) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        NULL,
                        "xmlSecTransformNodeRead",
                        XMLSEC_ERRORS_R_XMLSEC_FAILED,
                        "node=%s",
                        xmlSecErrorsSafeString(xmlSecNodeGetName(cur)));
            return(-1);
        }

        ret = xmlSecTransformCtxAppend(ctx, transform);
        if(ret < 0) {
            xmlSecError(XMLSEC_ERRORS_HERE,
                        NULL,
                        "xmlSecTransformCtxAppend",
                        XMLSEC_ERRORS_R_XMLSEC_FAILED,
                        "node=%s",
                        xmlSecErrorsSafeString(xmlSecNodeGetName(cur)));
            xmlSecTransformDestroy(transform);
            return(-1);
        }
        cur = xmlSecGetNextElementNode(cur->next);
    }

    if(cur != NULL) {
        xmlSecError(XMLSEC_ERRORS_HERE,
                    NULL,
                    xmlSecErrorsSafeString(xmlSecNodeGetName(cur)),
                    XMLSEC_ERRORS_R_UNEXPECTED_NODE,
                    XMLSEC_ERRORS_NO_MESSAGE);
        return(-1);
    }
    return(0);
}

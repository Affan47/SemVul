xmlSecTransformCtxCreate(void) {
    xmlSecTransformCtxPtr ctx;
    int ret;


    ctx = (xmlSecTransformCtxPtr)xmlMalloc(sizeof(xmlSecTransformCtx));
    if(ctx == NULL) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    NULL,
		    XMLSEC_ERRORS_R_MALLOC_FAILED,
		    "size=%d", sizeof(xmlSecTransformCtx));
	return(NULL);
    }

    ret = xmlSecTransformCtxInitialize(ctx);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecTransformCtxInitialize",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	xmlSecTransformCtxDestroy(ctx);
	return(NULL);
    }

    return(ctx);
}

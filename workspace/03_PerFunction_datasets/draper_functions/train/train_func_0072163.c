xmlSecDSigReferenceCtxCreate(xmlSecDSigCtxPtr dsigCtx, xmlSecDSigReferenceOrigin origin) {
    xmlSecDSigReferenceCtxPtr dsigRefCtx;
    int ret;

    xmlSecAssert2(dsigCtx != NULL, NULL);

    dsigRefCtx = (xmlSecDSigReferenceCtxPtr) xmlMalloc(sizeof(xmlSecDSigReferenceCtx));
    if(dsigRefCtx == NULL) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    NULL,
		    XMLSEC_ERRORS_R_MALLOC_FAILED,
		    "sizeof(xmlSecDSigReferenceCtx)=%d",
		    sizeof(xmlSecDSigReferenceCtx));
	return(NULL);
    }

    ret = xmlSecDSigReferenceCtxInitialize(dsigRefCtx, dsigCtx, origin);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecDSigReferenceCtxInitialize",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	xmlSecDSigReferenceCtxDestroy(dsigRefCtx);
	return(NULL);
    }
    return(dsigRefCtx);
}

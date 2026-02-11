xmlSecDSigCtxInitialize(xmlSecDSigCtxPtr dsigCtx, xmlSecKeysMngrPtr keysMngr) {
    int ret;

    xmlSecAssert2(dsigCtx != NULL, -1);

    memset(dsigCtx, 0, sizeof(xmlSecDSigCtx));


    ret = xmlSecKeyInfoCtxInitialize(&(dsigCtx->keyInfoReadCtx), keysMngr);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecKeyInfoCtxInitialize",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(-1);
    }
    dsigCtx->keyInfoReadCtx.mode = xmlSecKeyInfoModeRead;

    ret = xmlSecKeyInfoCtxInitialize(&(dsigCtx->keyInfoWriteCtx), keysMngr);
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecKeyInfoCtxInitialize",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(-1);
    }
    dsigCtx->keyInfoWriteCtx.mode = xmlSecKeyInfoModeWrite;

    dsigCtx->keyInfoWriteCtx.keyReq.keyType = xmlSecKeyDataTypePublic;


    ret = xmlSecTransformCtxInitialize(&(dsigCtx->transformCtx));
    if(ret < 0) {
	xmlSecError(XMLSEC_ERRORS_HERE,
		    NULL,
		    "xmlSecTransformCtxInitialize",
		    XMLSEC_ERRORS_R_XMLSEC_FAILED,
		    XMLSEC_ERRORS_NO_MESSAGE);
	return(-1);
    }


    xmlSecPtrListInitialize(&(dsigCtx->signedInfoReferences),
			    xmlSecDSigReferenceCtxListId);
    xmlSecPtrListInitialize(&(dsigCtx->manifestReferences),
			    xmlSecDSigReferenceCtxListId);

    dsigCtx->enabledReferenceUris = xmlSecTransformUriTypeAny;
    return(0);
}

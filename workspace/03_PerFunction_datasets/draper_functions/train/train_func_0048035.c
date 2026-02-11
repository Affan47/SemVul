xmlSecDSigCtxGetPreSignBuffer(xmlSecDSigCtxPtr dsigCtx) {
    xmlSecAssert2(dsigCtx != NULL, NULL);

    return((dsigCtx->preSignMemBufMethod != NULL) ?
	    xmlSecTransformMemBufGetBuffer(dsigCtx->preSignMemBufMethod) : NULL);
}

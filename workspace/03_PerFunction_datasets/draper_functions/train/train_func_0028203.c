xmlSecNssKeyTransportCtxUpdate(
	xmlSecNssKeyTransportCtxPtr		ctx ,
	xmlSecBufferPtr 			in ,
	xmlSecBufferPtr 			out ,
	int 						encrypt ,
	xmlSecTransformCtxPtr 		transformCtx
) {
	xmlSecAssert2( ctx != NULL , -1 ) ;
	xmlSecAssert2( ctx->cipher != CKM_INVALID_MECHANISM , -1 ) ;
	xmlSecAssert2( ( ctx->pubkey != NULL && encrypt ) || ( ctx->prikey != NULL && !encrypt ), -1 ) ;
	xmlSecAssert2( ctx->keyId != NULL , -1 ) ;
	xmlSecAssert2( ctx->material != NULL , -1 ) ;
	xmlSecAssert2( in != NULL , -1 ) ;
	xmlSecAssert2( out != NULL , -1 ) ;
	xmlSecAssert2( transformCtx != NULL , -1 ) ;


	if( xmlSecBufferAppend( ctx->material, xmlSecBufferGetData(in), xmlSecBufferGetSize(in) ) < 0 ) {
		xmlSecError( XMLSEC_ERRORS_HERE ,
			NULL ,
			"xmlSecBufferAppend" ,
			XMLSEC_ERRORS_R_CRYPTO_FAILED ,
			XMLSEC_ERRORS_NO_MESSAGE ) ;
		return(-1);
	}

	if( xmlSecBufferRemoveHead( in , xmlSecBufferGetSize(in) ) < 0 ) {
		xmlSecError( XMLSEC_ERRORS_HERE ,
			NULL ,
			"xmlSecBufferRemoveHead" ,
			XMLSEC_ERRORS_R_CRYPTO_FAILED ,
			XMLSEC_ERRORS_NO_MESSAGE ) ;
		return(-1);
	}

	return(0);
}

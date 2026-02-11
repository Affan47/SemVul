xmlSecNssKeyTransportFinalize(xmlSecTransformPtr transform) {
	xmlSecNssKeyTransportCtxPtr context ;

    xmlSecAssert(xmlSecNssKeyTransportCheckId(transform));
    xmlSecAssert(xmlSecTransformCheckSize(transform, xmlSecNssKeyTransportSize));

	context = xmlSecNssKeyTransportGetCtx( transform ) ;
	xmlSecAssert( context != NULL ) ;

	if( context->pubkey != NULL ) {
		SECKEY_DestroyPublicKey( context->pubkey ) ;
		context->pubkey = NULL ;
	}

	if( context->prikey != NULL ) {
		SECKEY_DestroyPrivateKey( context->prikey ) ;
		context->prikey = NULL ;
	}

	if( context->material != NULL ) {
		xmlSecBufferDestroy(context->material);
		context->material = NULL ;
	}
}

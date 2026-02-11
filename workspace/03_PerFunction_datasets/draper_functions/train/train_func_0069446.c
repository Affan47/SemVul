xmlSecNssKeyWrapSetKey(xmlSecTransformPtr transform, xmlSecKeyPtr key) {
    xmlSecNssKeyWrapCtxPtr context = NULL ;
    xmlSecKeyDataPtr    keyData = NULL ;
    PK11SymKey*         symkey = NULL ;

    xmlSecAssert2(xmlSecNssKeyWrapCheckId(transform), -1);
    xmlSecAssert2(xmlSecTransformCheckSize(transform, xmlSecNssKeyWrapSize), -1);
    xmlSecAssert2((transform->operation == xmlSecTransformOperationEncrypt) || (transform->operation == xmlSecTransformOperationDecrypt), -1);
    xmlSecAssert2(key != NULL, -1);

    context = xmlSecNssKeyWrapGetCtx( transform ) ;
    if( context == NULL || context->keyId == NULL || context->symkey != NULL ) {
        xmlSecError( XMLSEC_ERRORS_HERE ,
            xmlSecErrorsSafeString( xmlSecTransformGetName( transform ) ) ,
            "xmlSecNssKeyWrapGetCtx" ,
            XMLSEC_ERRORS_R_CRYPTO_FAILED ,
            XMLSEC_ERRORS_NO_MESSAGE ) ;
        return(-1);
    }
    xmlSecAssert2( xmlSecKeyCheckId( key, context->keyId ), -1 ) ;

    keyData = xmlSecKeyGetValue( key ) ;
    if( keyData == NULL ) {
        xmlSecError( XMLSEC_ERRORS_HERE ,
            xmlSecErrorsSafeString( xmlSecKeyGetName( key ) ) ,
            "xmlSecKeyGetValue" ,
            XMLSEC_ERRORS_R_CRYPTO_FAILED ,
            XMLSEC_ERRORS_NO_MESSAGE ) ;
        return(-1);
    }

    if( ( symkey = xmlSecNssSymKeyDataGetKey( keyData ) ) == NULL ) {
        xmlSecError( XMLSEC_ERRORS_HERE ,
            xmlSecErrorsSafeString( xmlSecKeyDataGetName( keyData ) ) ,
            "xmlSecNssSymKeyDataGetKey" ,
            XMLSEC_ERRORS_R_CRYPTO_FAILED ,
            XMLSEC_ERRORS_NO_MESSAGE ) ;
        return(-1);
    }

    context->symkey = symkey ;

    return(0) ;
}

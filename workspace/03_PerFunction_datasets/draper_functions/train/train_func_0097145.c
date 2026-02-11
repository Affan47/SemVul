xmlSecNssKeySlotCopy(
    xmlSecNssKeySlotPtr newKeySlot ,
    xmlSecNssKeySlotPtr keySlot
) {
    CK_MECHANISM_TYPE_PTR mech ;
    int counter ;

    xmlSecAssert2( newKeySlot != NULL , -1 ) ;
    xmlSecAssert2( keySlot != NULL , -1 ) ;

    if( keySlot->slot != NULL && newKeySlot->slot != keySlot->slot ) {
        if( newKeySlot->slot != NULL )
            PK11_FreeSlot( newKeySlot->slot ) ;

        newKeySlot->slot = PK11_ReferenceSlot( keySlot->slot ) ;
    }

    if( keySlot->mechanismList != CK_NULL_PTR ) {
        xmlFree( newKeySlot->mechanismList ) ;

        for( counter = 0 ; *( keySlot->mechanismList + counter ) != CKM_INVALID_MECHANISM ; counter ++ ) ;
        newKeySlot->mechanismList = ( CK_MECHANISM_TYPE_PTR )xmlMalloc( ( counter + 1 ) * sizeof( CK_MECHANISM_TYPE ) ) ;
        if( newKeySlot->mechanismList == NULL ) {
            xmlSecError( XMLSEC_ERRORS_HERE ,
                NULL ,
                NULL ,
                XMLSEC_ERRORS_R_XMLSEC_FAILED ,
                XMLSEC_ERRORS_NO_MESSAGE ) ;
            return( -1 );
        }
        for( ; counter >= 0 ; counter -- )
            *( newKeySlot->mechanismList + counter ) = *(  keySlot->mechanismList + counter ) ;
    }

    return( 0 );
}

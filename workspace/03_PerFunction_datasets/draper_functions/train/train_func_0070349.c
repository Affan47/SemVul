WXMPIterator_PropCTor_1 ( XMPMetaRef     xmpRef,
                          XMP_StringPtr  schemaNS,
                          XMP_StringPtr  propName,
                          XMP_OptionBits options,
                          WXMP_Result *  wResult )
{
    XMP_ENTER_WRAPPER ( "WXMPIterator_PropCTor_1" )

		if ( schemaNS == 0 ) schemaNS = "";
		if ( propName == 0 ) propName = "";

		const XMPMeta & xmpObj = WtoXMPMeta_Ref ( xmpRef );
		XMPIterator *   iter   = new XMPIterator ( xmpObj, schemaNS, propName, options );
		++iter->clientRefs;
		XMP_Assert ( iter->clientRefs == 1 );
		wResult->ptrResult = XMPIteratorRef ( iter );

    XMP_EXIT_WRAPPER
}

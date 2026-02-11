WXMPMeta_GetLocalizedText_1 ( XMPMetaRef	   xmpRef,
							  XMP_StringPtr	   schemaNS,
							  XMP_StringPtr	   arrayName,
							  XMP_StringPtr	   genericLang,
							  XMP_StringPtr	   specificLang,
							  XMP_StringPtr *  actualLang,
							  XMP_StringLen *  langSize,
							  XMP_StringPtr *  itemValue,
							  XMP_StringLen *  valueSize,
							  XMP_OptionBits * options,
							  WXMP_Result *	   wResult )
{
	XMP_ENTER_WRAPPER ( "WXMPMeta_GetLocalizedText_1" )

		if ( (schemaNS == 0) || (*schemaNS == 0) ) XMP_Throw ( "Empty schema namespace URI", kXMPErr_BadSchema );
		if ( (arrayName == 0) || (*arrayName == 0) ) XMP_Throw ( "Empty array name", kXMPErr_BadXPath );
		if ( genericLang == 0 ) genericLang = "";
		if ( (specificLang == 0) ||(*specificLang == 0) ) XMP_Throw ( "Empty specific language", kXMPErr_BadParam );

		if ( actualLang == 0 ) actualLang = &voidStringPtr;
		if ( langSize == 0 ) langSize = &voidStringLen;
		if ( itemValue == 0 ) itemValue = &voidStringPtr;
		if ( valueSize == 0 ) valueSize = &voidStringLen;
		if ( options == 0 ) options = &voidOptionBits;

		const XMPMeta & meta = WtoXMPMeta_Ref ( xmpRef );
		bool found = meta.GetLocalizedText ( schemaNS, arrayName, genericLang, specificLang,
											 actualLang, langSize, itemValue, valueSize, options );
		wResult->int32Result = found;

	XMP_EXIT_WRAPPER_KEEP_LOCK ( found )
}

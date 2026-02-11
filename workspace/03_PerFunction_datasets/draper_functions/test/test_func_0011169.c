WXMPMeta_GetLocalizedText_1 ( XMPMetaRef	   xmpObjRef,
							  XMP_StringPtr	   schemaNS,
							  XMP_StringPtr	   arrayName,
							  XMP_StringPtr	   genericLang,
							  XMP_StringPtr	   specificLang,
							  void *           actualLang,
							  void *           itemValue,
							  XMP_OptionBits * options,
							  SetClientStringProc SetClientString,
							  WXMP_Result *	   wResult )
{
	XMP_ENTER_ObjRead ( XMPMeta, "WXMPMeta_GetLocalizedText_1" )

		if ( (schemaNS == 0) || (*schemaNS == 0) ) XMP_Throw ( "Empty schema namespace URI", kXMPErr_BadSchema );
		if ( (arrayName == 0) || (*arrayName == 0) ) XMP_Throw ( "Empty array name", kXMPErr_BadXPath );
		if ( genericLang == 0 ) genericLang = "";
		if ( (specificLang == 0) ||(*specificLang == 0) ) XMP_Throw ( "Empty specific language", kXMPErr_BadParam );

		XMP_StringPtr langPtr = 0;
		XMP_StringLen langSize = 0;
		XMP_StringPtr valuePtr = 0;
		XMP_StringLen valueSize = 0;
		if ( options == 0 ) options = &voidOptionBits;

		bool found = thiz.GetLocalizedText ( schemaNS, arrayName, genericLang, specificLang,
											 &langPtr, &langSize, &valuePtr, &valueSize, options );
		wResult->int32Result = found;

		if ( found ) {
			if ( actualLang != 0 ) (*SetClientString) ( actualLang, langPtr, langSize );
			if ( itemValue != 0 ) (*SetClientString) ( itemValue, valuePtr, valueSize );
		}

	XMP_EXIT
}

WXMPMeta_GetArrayItem_1 ( XMPMetaRef	   xmpObjRef,
						  XMP_StringPtr	   schemaNS,
						  XMP_StringPtr	   arrayName,
						  XMP_Index		   itemIndex,
						  void *           itemValue,
						  XMP_OptionBits * options,
						  SetClientStringProc SetClientString,
						  WXMP_Result *	   wResult )
{
	XMP_ENTER_ObjRead ( XMPMeta, "WXMPMeta_GetArrayItem_1" )

		if ( (schemaNS == 0) || (*schemaNS == 0) ) XMP_Throw ( "Empty schema namespace URI", kXMPErr_BadSchema );
		if ( (arrayName == 0) || (*arrayName == 0) ) XMP_Throw ( "Empty array name", kXMPErr_BadXPath );

		XMP_StringPtr valuePtr = 0;
		XMP_StringLen valueSize = 0;
		if ( options == 0 ) options = &voidOptionBits;

		bool found = thiz.GetArrayItem ( schemaNS, arrayName, itemIndex, &valuePtr, &valueSize, options );
		wResult->int32Result = found;

		if ( found && (itemValue != 0) ) (*SetClientString) ( itemValue, valuePtr, valueSize );

	XMP_EXIT
}

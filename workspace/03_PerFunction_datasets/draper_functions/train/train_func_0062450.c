WXMPMeta_GetProperty_1 ( XMPMetaRef		  xmpObjRef,
						 XMP_StringPtr	  schemaNS,
						 XMP_StringPtr	  propName,
						 void *           propValue,
						 XMP_OptionBits * options,
						 SetClientStringProc SetClientString,
						 WXMP_Result *	  wResult )
{
	XMP_ENTER_ObjRead ( XMPMeta, "WXMPMeta_GetProperty_1" )

		if ( (schemaNS == 0) || (*schemaNS == 0) ) XMP_Throw ( "Empty schema namespace URI", kXMPErr_BadSchema );
		if ( (propName == 0) || (*propName == 0) ) XMP_Throw ( "Empty property name", kXMPErr_BadXPath );

		XMP_StringPtr valuePtr = 0;
		XMP_StringLen valueSize = 0;
		if ( options == 0 ) options = &voidOptionBits;

		bool found = thiz.GetProperty ( schemaNS, propName, &valuePtr, &valueSize, options );
		wResult->int32Result = found;

		if ( found && (propValue != 0) ) (*SetClientString) ( propValue, valuePtr, valueSize );

	XMP_EXIT
}

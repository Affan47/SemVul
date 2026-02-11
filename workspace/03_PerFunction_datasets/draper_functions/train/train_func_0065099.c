WXMPMeta_DeleteProperty_1 ( XMPMetaRef	  xmpObjRef,
							XMP_StringPtr schemaNS,
							XMP_StringPtr propName,
							WXMP_Result * wResult )
{
	XMP_ENTER_ObjWrite ( XMPMeta, "WXMPMeta_DeleteProperty_1" )

		if ( (schemaNS == 0) || (*schemaNS == 0) ) XMP_Throw ( "Empty schema namespace URI", kXMPErr_BadSchema );
		if ( (propName == 0) || (*propName == 0) ) XMP_Throw ( "Empty property name", kXMPErr_BadXPath );

		thiz->DeleteProperty ( schemaNS, propName );

	XMP_EXIT
}

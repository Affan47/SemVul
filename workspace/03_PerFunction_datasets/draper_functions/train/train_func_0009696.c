WXMPMeta_DoesStructFieldExist_1 ( XMPMetaRef	xmpRef,
								  XMP_StringPtr schemaNS,
								  XMP_StringPtr structName,
								  XMP_StringPtr fieldNS,
								  XMP_StringPtr fieldName,
								  WXMP_Result * wResult )
{
	XMP_ENTER_WRAPPER ( "WXMPMeta_DoesStructFieldExist_1" )

		if ( (schemaNS == 0) || (*schemaNS == 0) ) XMP_Throw ( "Empty schema namespace URI", kXMPErr_BadSchema );
		if ( (structName == 0) || (*structName == 0) ) XMP_Throw ( "Empty struct name", kXMPErr_BadXPath );
		if ( (fieldNS == 0) || (*fieldNS == 0) ) XMP_Throw ( "Empty field namespace URI", kXMPErr_BadSchema );
		if ( (fieldName == 0) || (*fieldName == 0) ) XMP_Throw ( "Empty field name", kXMPErr_BadXPath );

		const XMPMeta & meta = WtoXMPMeta_Ref ( xmpRef );
		bool found = meta.DoesStructFieldExist ( schemaNS, structName, fieldNS, fieldName );
		wResult->int32Result = found;

	XMP_EXIT_WRAPPER
}

WXMPMeta_DeleteArrayItem_1 ( XMPMetaRef	   xmpRef,
							 XMP_StringPtr schemaNS,
							 XMP_StringPtr arrayName,
							 XMP_Index	   itemIndex,
							 WXMP_Result * wResult )
{
	XMP_ENTER_WRAPPER ( "WXMPMeta_DeleteArrayItem_1" )

		if ( (schemaNS == 0) || (*schemaNS == 0) ) XMP_Throw ( "Empty schema namespace URI", kXMPErr_BadSchema );
		if ( (arrayName == 0) || (*arrayName == 0) ) XMP_Throw ( "Empty array name", kXMPErr_BadXPath );

		XMPMeta * meta = WtoXMPMeta_Ptr ( xmpRef );
		meta->DeleteArrayItem ( schemaNS, arrayName, itemIndex );

	XMP_EXIT_WRAPPER
}

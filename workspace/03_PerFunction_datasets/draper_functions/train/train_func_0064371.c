WXMPMeta_GetProperty_Float_1 ( XMPMetaRef		xmpRef,
							   XMP_StringPtr	schemaNS,
							   XMP_StringPtr	propName,
							   double *			propValue,
							   XMP_OptionBits * options,
							   WXMP_Result *	wResult )
{
	XMP_ENTER_WRAPPER ( "WXMPMeta_GetProperty_Float_1" )

		if ( (schemaNS == 0) || (*schemaNS == 0) ) XMP_Throw ( "Empty schema namespace URI", kXMPErr_BadSchema );
		if ( (propName == 0) || (*propName == 0) ) XMP_Throw ( "Empty property name", kXMPErr_BadXPath );

		if ( propValue == 0 ) propValue = &voidDouble;
		if ( options == 0 ) options = &voidOptionBits;

		const XMPMeta & meta = WtoXMPMeta_Ref ( xmpRef );
		bool found = meta.GetProperty_Float ( schemaNS, propName, propValue, options );
		wResult->int32Result = found;

	XMP_EXIT_WRAPPER
}

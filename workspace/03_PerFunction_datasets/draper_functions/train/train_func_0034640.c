WXMPUtils_ConvertFromDate_1 ( const XMP_DateTime & binValue,
							  XMP_StringPtr *	   strValue,
							  XMP_StringLen *	   strSize,
							  WXMP_Result *		   wResult )
{
	XMP_ENTER_WRAPPER ( "WXMPUtils_ConvertFromDate_1" )

		if ( strValue == 0 ) strValue = &voidStringPtr;
		if ( strSize == 0 ) strSize = &voidStringLen;

		XMPUtils::ConvertFromDate( binValue, strValue, strSize );

	XMP_EXIT_WRAPPER_KEEP_LOCK ( true )
}

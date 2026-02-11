WXMPUtils_ConvertFromInt64_1 ( XMP_Int64	 binValue,
							   XMP_StringPtr format,
							   void *        strValue,
							   SetClientStringProc SetClientString,
							   WXMP_Result * wResult )
{
	XMP_ENTER_Static ( "WXMPUtils_ConvertFromInt64_1" )

		if ( format == 0 ) format = "";

		XMP_VarString localStr;

		XMPUtils::ConvertFromInt64 ( binValue, format, &localStr );
		if ( strValue != 0 ) (*SetClientString) ( strValue, localStr.c_str(), localStr.size() );

	XMP_EXIT
}

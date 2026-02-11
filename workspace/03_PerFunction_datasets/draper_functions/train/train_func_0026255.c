ConvertToInt ( XMP_StringPtr strValue )
{
	if ( (strValue == 0) || (*strValue == 0) ) XMP_Throw ( "Empty convert-from string", kXMPErr_BadValue );

	int count;
	char nextCh;
	XMP_Int32 result;

	if ( ! XMP_LitNMatch ( strValue, "0x", 2 ) ) {
		count = sscanf ( strValue, "%d%c", &result, &nextCh );
	} else {
		count = sscanf ( strValue, "%x%c", &result, &nextCh );
	}

	if ( count != 1 ) XMP_Throw ( "Invalid integer string", kXMPErr_BadParam );

	return result;

}

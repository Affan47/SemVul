GatherInt ( XMP_StringPtr strValue, size_t * _pos, const char * errMsg )
{
	size_t	 pos   = *_pos;
	XMP_Int32 value = 0;

	for ( char ch = strValue[pos]; ('0' <= ch) && (ch <= '9'); ++pos, ch = strValue[pos] ) {
		value = (value * 10) + (ch - '0');
	}

	if ( pos == *_pos ) XMP_Throw ( errMsg, kXMPErr_BadParam );
	*_pos = pos;
	return value;

}

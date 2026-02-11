QueryBoolValue( bool* value ) const
{
	int ival = -1;
	QueryIntValue( &ival );

	if ( ival > 0 || XMLUtil::StringEqual( Value(), "true" ) ) {
		*value = true;
		return XML_NO_ERROR;
	}
	else if ( ival == 0 || XMLUtil::StringEqual( Value(), "false" ) ) {
		*value = false;
		return XML_NO_ERROR;
	}
	return XML_WRONG_ATTRIBUTE_TYPE;
}

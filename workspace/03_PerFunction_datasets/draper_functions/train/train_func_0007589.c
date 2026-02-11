Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding )
{
	TiXmlDocument* document = GetDocument();
	value = "";

	p = SkipWhiteSpace( p, encoding );

	if ( data )
	{
		data->Stamp( p, encoding );
		location = data->Cursor();
	}
	const char* startTag = "<!--";
	const char* endTag   = "-->";

	if ( !StringEqual( p, startTag, false, encoding ) )
	{
		document->SetError( TIXML_ERROR_PARSING_COMMENT, p, data, encoding );
		return 0;
	}
	p += strlen( startTag );


    value = "";

	while (	p && *p && !StringEqual( p, endTag, false, encoding ) )
	{
		value.append( p, 1 );
		++p;
	}
	if ( p )
		p += strlen( endTag );

	return p;
}

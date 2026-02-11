Parse( const char* p )
{
	TiXmlDocument* document = GetDocument();
	p = SkipWhiteSpace( p );
	if ( !p || !*p )
	{
		if ( document ) document->SetError( TIXML_ERROR_PARSING_ELEMENT );
		return 0;
	}


	p = ReadName( p, &value );
	if ( !p )
	{
		if ( document )	document->SetError( TIXML_ERROR_FAILED_TO_READ_ELEMENT_NAME );
		return 0;
	}

	std::string endTag = "</";
	endTag += value;
	endTag += ">";


	while ( p && *p )
	{
		p = SkipWhiteSpace( p );
		if ( !p || !*p )
		{
			if ( document ) document->SetError( TIXML_ERROR_READING_ATTRIBUTES );
			return 0;
		}
		if ( *p == '/' )
		{

			if ( *(p+1) != '>' )
			{
				if ( document ) document->SetError( TIXML_ERROR_PARSING_EMPTY );
				return 0;
			}
			return p+2;
		}
		else if ( *p == '>' )
		{


			p = ReadValue( p+1 );
			if ( !p )
				return 0;


			std::string buf( p, endTag.size() );
			if ( endTag == buf )
			{
				return p+endTag.size();
			}
			else
			{
				if ( document ) document->SetError( TIXML_ERROR_READING_END_TAG );
				return 0;
			}
		}
		else
		{

			TiXmlAttribute attrib;
			attrib.SetDocument( document );
			p = attrib.Parse( p );

			if ( p )
			{
				SetAttribute( attrib.Name(), attrib.Value() );
			}
		}
	}
	return 0;
}

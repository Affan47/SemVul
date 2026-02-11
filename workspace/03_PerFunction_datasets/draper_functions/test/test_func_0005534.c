ReadText(	const char* p,
									TIXML_STRING * text,
									bool trimWhiteSpace,
									const char* endTag,
									bool caseInsensitive,
									TiXmlEncoding encoding )
{
    *text = "";
	if (    !trimWhiteSpace
		 || !condenseWhiteSpace )
	{

		while (	   p && *p
				&& !StringEqual( p, endTag, caseInsensitive, encoding )
			  )
		{
			int len;
			char cArr[4] = { 0, 0, 0, 0 };
			p = GetChar( p, cArr, &len, encoding );
			text->append( cArr, len );
		}
	}
	else
	{
		bool whitespace = false;


		p = SkipWhiteSpace( p, encoding );
		while (	   p && *p
				&& !StringEqual( p, endTag, caseInsensitive, encoding ) )
		{
			if ( *p == '\r' || *p == '\n' )
			{
				whitespace = true;
				++p;
			}
			else if ( IsWhiteSpace( *p ) )
			{
				whitespace = true;
				++p;
			}
			else
			{


				if ( whitespace )
				{
					(*text) += ' ';
					whitespace = false;
				}
				int len;
				char cArr[4] = { 0, 0, 0, 0 };
				p = GetChar( p, cArr, &len, encoding );
				if ( len == 1 )
					(*text) += cArr[0];
				else
					text->append( cArr, len );
			}
		}
	}
	if ( p && *p )
		p += strlen( endTag );
	return ( p && *p ) ? p : 0;
}

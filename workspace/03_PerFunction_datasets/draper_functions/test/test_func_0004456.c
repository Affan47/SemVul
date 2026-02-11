SkipWhiteSpace( const char* p, TiXmlEncoding encoding )
{
	if ( !p || !*p )
	{
		return 0;
	}
	if ( encoding == TIXML_ENCODING_UTF8 )
	{
		while ( *p )
		{
			const unsigned char* pU = (const unsigned char*)p;


			if (	*(pU+0)==TIXML_UTF_LEAD_0
				 && *(pU+1)==TIXML_UTF_LEAD_1
				 && *(pU+2)==TIXML_UTF_LEAD_2 )
			{
				p += 3;
				continue;
			}
			else if(*(pU+0)==TIXML_UTF_LEAD_0
				 && *(pU+1)==0xbfU
				 && *(pU+2)==0xbeU )
			{
				p += 3;
				continue;
			}
			else if(*(pU+0)==TIXML_UTF_LEAD_0
				 && *(pU+1)==0xbfU
				 && *(pU+2)==0xbfU )
			{
				p += 3;
				continue;
			}

			if ( IsWhiteSpace( *p ) || *p == '\n' || *p =='\r' )
				++p;
			else
				break;
		}
	}
	else
	{
		while ( *p && IsWhiteSpace( *p ) || *p == '\n' || *p =='\r' )
			++p;
	}

	return p;
}

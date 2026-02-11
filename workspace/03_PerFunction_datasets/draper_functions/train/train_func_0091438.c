StreamIn( std::istream * in, TIXML_STRING * tag )
{
	while ( in->good() )
	{
		int c = in->get();
		if ( c <= 0 )
		{
			TiXmlDocument* document = GetDocument();
			if ( document )
				document->SetError( TIXML_ERROR_EMBEDDED_NULL, 0, 0, TIXML_ENCODING_UNKNOWN );
			return;
		}
		(*tag) += (char) c;

		if ( c == '>' )
		{

			return;
		}
	}
}

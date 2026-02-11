LoadFile( const char* _filename, TiXmlEncoding encoding )
{


	TIXML_STRING filename( _filename );
	value = filename;


	FILE* file = TiXmlFOpen( value.c_str (), "rb" );

	if ( file )
	{
		bool result = LoadFile( file, encoding );
		fclose( file );
		return result;
	}
	else
	{
		SetError( TIXML_ERROR_OPENING_FILE, 0, 0, TIXML_ENCODING_UNKNOWN );
		return false;
	}
}

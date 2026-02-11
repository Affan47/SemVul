Print( FILE* cfile, int  ) const
{
	TIXML_STRING buffer;
	PutString( value, &buffer );
	fprintf( cfile, "%s", buffer.c_str() );
}

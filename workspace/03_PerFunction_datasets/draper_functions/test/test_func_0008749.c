ignoreCase( const char * in, char * out )
{

	bool inRange = 0;
	while( *in )
	{
		if ( *in == '[' )
			inRange = 1;
		if ( *in == ']' )
			inRange = 0;
		if ( ! inRange && isalpha( *in ) )
		{
			*out++ = '[';
			*out++ = (char)toupper( *in );
			*out++ = (char)tolower( *in );
			*out++ = ']';
		}
		else
			*out++ = *in;
		in++;
	}
	*out = 0;
}

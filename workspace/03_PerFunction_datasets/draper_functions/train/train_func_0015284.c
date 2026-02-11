parseStartLine( SP_HttpMessage ** message,
		const void * buffer, int len )
{
	int lineLen = 0;

	char * pos = (char*)memchr( buffer, '\n', len );
	if( NULL != pos ) {
		lineLen = pos - (char*)buffer + 1;

		char * line = (char*)malloc( lineLen + 1 );
		memcpy( line, buffer, lineLen );
		line[ lineLen ] = '\0';

		pos = line;

		char * first, * second;
		first = sp_strsep( &pos, " " );
		second = sp_strsep( &pos, " " );

		if( 0 == strncasecmp( line, "HTTP", 4 ) ) {
			SP_HttpResponse * response = new SP_HttpResponse();
			if( NULL != first ) response->setVersion( first );
			if( NULL != second ) response->setStatusCode( atoi( second ) );
			if( NULL != pos ) response->setReasonPhrase( strtok( pos, "\r\n" ) );

			*message = response;
		} else {
			SP_HttpRequest * request = new SP_HttpRequest();
			if( NULL != first ) request->setMethod( first );
			if( NULL != second ) request->setURL( second );
			if( NULL != second ) request->setURI( sp_strsep( &second, "?" ) );
			if( NULL != pos ) request->setVersion( strtok( pos, "\r\n" ) );

			char * params = second;
			for( ; NULL != params && '\0' != *params; ) {
				char * value = sp_strsep( &params, "&" );
				char * name = sp_strsep( &value, "=" );
				request->addParam( name, NULL == value ? "" : value );
			}

			*message = request;
		}

		free( line );
	}

	return lineLen;
}

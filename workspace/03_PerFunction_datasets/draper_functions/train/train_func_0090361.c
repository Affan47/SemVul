postProcess( SP_HttpMessage * message )
{
	if( SP_HttpMessage::eRequest == message->getType() ) {
		SP_HttpRequest * request = (SP_HttpRequest*)message;
		const char * contentType = request->getHeaderValue(
			SP_HttpMessage::HEADER_CONTENT_TYPE );
		if( request->getContentLength() > 0 && NULL != contentType
			&& 0 == strcasecmp( contentType, "application/x-www-form-urlencoded" ) ) {

			char * content = (char*)malloc( request->getContentLength() + 1 );
			memcpy( content, request->getContent(), request->getContentLength() );
			content[ request->getContentLength() ] = '\0';

			char * params = content;
			for( ; NULL != params && '\0' != *params; ) {
				char * value = sp_strsep( &params, "&" );
				char * name = sp_strsep( &value, "=" );
				request->addParam( name, NULL == value ? "" : value );
			}

			free( content );
		}
	}
}

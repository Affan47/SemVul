handleDefFunction( void* ud, uint32_t streamid,
	uint32_t func, const char* name, uint32_t , uint32_t  ) {


	map<uint32_t, Filter>::iterator it = ((HandlerArgument*)ud)->p2f.find( 0 );

	string escaped;

	for( uint32_t i= 0; i < strlen(name); ++i ) {

		if( '*' == name[i] ) {
			escaped.append( 1, '\\' );
		}

		escaped.append( 1, name[i] );
	}


	it->second.addFunction( func, escaped );


	return OTF_RETURN_OK;
}

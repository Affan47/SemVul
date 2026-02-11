handler_connector( HttpMessage& request, HttpMessage& response ){
	response_options_t out;
	ConnectorMessage msg;
	SaigaConnector connector( "/tmp/default.saiga" );
	uint64_t cache_msecs;

	bool connected = connector.start();
	if( !connected ){
		throw std::string( "No one to connect to!" );
		}

	msg = connector.process( request );

	if( msg.get( "status") != "ok" ){
		out.ok = false;
		return out;
		}

	response.set_body( msg.get( "body" ) );
	response.set_code( string_to_integer( msg.get( "code" ) ) );
	response.set_code_string( "Ok." );
	out.ok = true;
	cache_msecs = string_to_integer( msg.get( "cache" ) );
	if( cache_msecs == 0 ){
		out.cached = false;
		}
	else{
		out.cached = true;
		out.expires = cache_msecs / 1000.0;
		}


	std::vector< std::string > fields = msg.get_keys();
	for( size_t i = 0 ; i < fields.size() ; ++i ){
		if( string_startswith( "header.", fields[i] ) ){
			std::string field = fields[i].substr( strlen( "header." ) );
			std::vector< std::string > parts = split_string( field, ":" );
			std::string key, value;
			key = trim( parts[0] );
			if( parts.size() > 2 ){
				value = parts[1];
				for( size_t j = 2 ; j < parts.size() ; ++j ){
					value += ":" + parts[j];
					}
				}
			value = trim( value );
			response.set_header_field( key, value );
			}
		}

	return out;
	}

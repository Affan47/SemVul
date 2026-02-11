to_pstr( std::string str ){
	uint64_t len;
	char buffer[32];
	memset( buffer, 0, 32 );
	len = str.size();
	memcpy( buffer, &len, sizeof( uint64_t ) );
	return std::string( buffer, sizeof( uint64_t ) ) + str;
	}

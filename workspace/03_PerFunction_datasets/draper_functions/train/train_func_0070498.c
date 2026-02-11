checkServerLink( const string& uri )
{
	if ( uri.substr( 0, 15 ) == "ed2k://|server|" ) {
		size_t base_off = 14;
		size_t host_off = uri.find( '|', base_off + 1 );
		size_t port_off = uri.find( '|', host_off + 1 );

		bool valid = true;
		valid &= ( base_off < host_off );
		valid &= ( host_off < port_off );
		valid &= ( port_off != string::npos );

		if ( !valid || uri.at( port_off + 1 ) != '/' ) {
			badLink( "server", "invalid link format", uri );
			return false;
		}

		string host = uri.substr( base_off + 1, host_off - base_off - 1 );
		string port = uri.substr( host_off + 1, port_off - host_off - 1 );

		if ( host.empty() ) {
			badLink( "server", "no hostname specified", uri );
			return false;
		}

		if ( !isNumber( port ) ) {
			badLink( "server", "invalid port", uri );
			return false;
		}

		return true;
	}

	return false;
}

set_used_sectors( Partition & partition )
{
	exit_status = Utils::execute_command( check_cmd + " -n -v " + partition .get_path(), output, error, true ) ;
	if ( exit_status == 0 || exit_status == 1 || exit_status == 256 )
	{

		index = output .rfind( "\n", output .find( "sectors total" ) ) +1 ;
		if ( index >= output .length() || sscanf( output .substr( index ) .c_str(), "%Ld", &T ) != 1 )
			T = -1 ;


		index = output .rfind( "\n", output .find( "bytes per logical sector" ) ) +1 ;
		if ( index >= output .length() || sscanf( output .substr( index ) .c_str(), "%Ld", &S ) != 1 )
			S = -1 ;

		if ( T > -1 && S > -1 )
			T = Utils::round( T * ( S / double(partition .sector_size) ) ) ;


		index = output .find( ",", output .find( partition .get_path() ) + partition .get_path() .length() ) +1 ;
		if ( index < output .length() && sscanf( output .substr( index ) .c_str(), "%Ld/%Ld", &S, &N ) == 2 )
			N -= S ;
		else
			N = -1 ;


		index = output .rfind( "\n", output .find( "bytes per cluster" ) ) +1 ;
		if ( index >= output .length() || sscanf( output .substr( index ) .c_str(), "%Ld", &S ) != 1 )
			S = -1 ;

		if ( N > -1 && S > -1 )
			N = Utils::round( N * ( S / double(partition .sector_size) ) ) ;

		if ( T > -1 && N > -1 )
			partition .set_sector_usage( T, N ) ;
	}
	else
	{
		if ( ! output .empty() )
			partition .messages .push_back( output ) ;

		if ( ! error .empty() )
			partition .messages .push_back( error ) ;
	}
}

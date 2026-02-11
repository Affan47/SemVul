set_used_sectors( Partition & partition )
{
	if ( ! Utils::execute_command( "debugfs.reiser4 " + partition .get_path(), output, error, true ) )
	{
		index = output .find( "\nblocks:" ) ;
		if ( index >= output .length() ||
		     sscanf( output.substr( index ) .c_str(), "\nblocks: %Ld", &T ) != 1 )
			T = -1 ;

		index = output .find( "\nfree blocks:" ) ;
		if ( index >= output .length() ||
		     sscanf( output.substr( index ) .c_str(), "\nfree blocks: %Ld", &N ) != 1 )
			N = -1 ;

		index = output .find( "\nblksize:" ) ;
		if ( index >= output.length() ||
		     sscanf( output.substr( index ) .c_str(), "\nblksize: %Ld", &S ) != 1 )
			S = -1 ;

		if ( T > -1 && N > -1 && S > -1 )
		{
			T = Utils::round( T * ( S / double(partition .sector_size) ) ) ;
			N = Utils::round( N * ( S / double(partition .sector_size) ) ) ;
			partition .set_sector_usage( T, N ) ;
		}
	}
	else
	{
		if ( ! output .empty() )
			partition .messages .push_back( output ) ;

		if ( ! error .empty() )
			partition .messages .push_back( error ) ;
	}
}

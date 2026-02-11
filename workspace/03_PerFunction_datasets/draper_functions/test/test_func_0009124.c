set_used_sectors( Partition & partition )
{
	if ( partition .busy )
	{
		T = -1 ; N = -1 ;
		std::string line ;
		std::ifstream input( "/proc/swaps" ) ;
		if ( input )
		{
			Glib::ustring path = partition .get_path() ;
			Glib::ustring::size_type path_len = path.length() ;
			while ( getline( input, line ) )
			{
				if ( line .substr( 0, path_len ) == path )
				{
					sscanf( line .substr( path_len ) .c_str(), " %*s %Ld %Ld", &T, &N ) ;
					break ;
				}
			}
			input .close() ;
		}
		else
		{
			partition .messages .push_back( "open(\"/proc/swaps\", O_RDONLY): " + Glib::strerror( errno ) ) ;
		}
		if ( T > -1 && N > -1 )
		{
			T = Utils::round( T * ( KIBIBYTE / double(partition .sector_size) ) ) ;
			N = Utils::round( N * ( KIBIBYTE / double(partition .sector_size) ) ) ;
			partition .set_sector_usage( T, T - N ) ;
		}
	}
	else
	{

		Sector size = partition .get_sector_length() ;
		partition .set_sector_usage( size, size ) ;
	}
}

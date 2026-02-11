get_gmt_time( size_t T ){
	char buffer[128];
	struct tm *time_ptr;
	size_t n;

	if( T == 0 ){
		time_t rawtime;
		time( &rawtime );

		time_ptr = gmtime( &rawtime );
		}
	else{
		time_t rawtime;
		rawtime = T;
		time_ptr = gmtime( &rawtime );
		}


	n = strftime( buffer, 128, "%a, %d %b %Y %H:%M:%S GMT", time_ptr );
	return std::string( buffer, n );
	}

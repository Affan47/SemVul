msgv( int vrb, const char *client_name, const char* fmt, va_list ap)
{


	if ( log_threshold < vrb && stdout_tee_threshold < vrb )
		return;

	char timestampbuf[32];
	time_t timestamp; time( &timestamp);
	struct timeval tp; gettimeofday( &tp, nullptr);
	strftime( timestampbuf, 31, "%F %T", localtime( &timestamp));
	char secfracbuf[sec_dec_places+3];
	snprintf( secfracbuf, sec_dec_places+2, ".%0*u", sec_dec_places,
		  (unsigned)round( tp.tv_usec / pow( 10., 6-sec_dec_places-1)));

	vsnprintf( _line_buf, _buf_size, fmt, ap);

	char *line = strtok( _line_buf, "\n");
	do {
		if ( vrb < 0 )
			printf( "%s%sError: %s\n", client_name ? client_name : "", (client_name && strlen(client_name)) ? ": " : "", line);
		else if ( stdout_tee_threshold >= vrb )
			printf( "%s%s%s\n", client_name ? client_name : "", (client_name && strlen(client_name)) ? ": " : "", line);

		if ( log_threshold >= vrb && _log_fname.size() )
			_log_strm << timestampbuf << (sec_dec_places > 0 ? secfracbuf : "") << ' '
				  << client_name << ": "
				  << (vrb < 0 ? "Error: " : "") << line << endl;
	} while ( (line = strtok( nullptr, "\n")) );

	if ( _log_fname.size() )
		_log_strm.flush();
}

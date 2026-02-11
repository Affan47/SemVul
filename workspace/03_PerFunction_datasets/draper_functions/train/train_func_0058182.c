check_packet_logging()
{
	char *log;

	log = getenv( "LOG_PACKETS" );
	if ( log && ( strcmp( log, "1" ) == 0 ) )
		log_packets = 1;
	else
		log_packets = 0;
}

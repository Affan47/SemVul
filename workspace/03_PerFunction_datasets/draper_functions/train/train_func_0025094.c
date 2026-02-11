main( int argc, char **argv ){

	ThreadHerd herd;

	signal(SIGPIPE, SIG_IGN);

	RequestHandler::add_handler( "/index", &handler_index );
	RequestHandler::add_handler( "/static/", &handler_static_files );
	RequestHandler::add_handler( "/api/", &handler_connector );

	try{
		herd.init( 8000 );
		herd.start();

		printf( "Press enter to stop... \n" );
		getc(stdin);

		herd.stop();
		} catch( std::string error ){
			std::cerr << "ERROR: " << error << std::endl;
			}
	return 0;


	}

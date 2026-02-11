start(){
	if( connected ){

		int rc;
		pthread_attr_t attr;

		running = true;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

		for( size_t i = 0 ; i < 128 ; ++i ){
			pthread_t handler;
			rc = pthread_create( &handler, &attr, &RequestHandler::workerThread, NULL );
			if( rc != 0 ){
				throw std::string( "Unable to start RH:worker thread." );
				}
			}


		rc = pthread_create( &worker, &attr, &ThreadHerd::_bootstap_thread, this );
		if( rc != 0 ){
			throw std::string( "Unable to start worker thread." );
			}


		rc = pthread_create( &cleaner, &attr, &RequestHandler::cleanerThread, NULL );
		if( rc != 0 ){
			throw std::string( "Unable to start cleaner thread." );
			}

		pthread_attr_destroy(&attr);

		}

	}

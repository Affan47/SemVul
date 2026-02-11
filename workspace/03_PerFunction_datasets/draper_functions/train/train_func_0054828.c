pit_gettimeofday( struct timeval *tp, struct timezone *foo,
	char *pit_hostname, char *pit_service)
{
	int            	sckt;
	unsigned scopeId = 0;


	if(pit_hostname[0] == 0)
	{
		return gettimeofday(tp,foo);
	}

 	if ( ( sckt = openSckt( pit_hostname,
                           pit_service,
                           scopeId ) ) == INVALID_DESC )
   	{
      		fprintf( stderr,
                  "Sorry... a connectionless socket could "
                  "not be set up.\n");
                return -1;
   	}


   	pit( sckt ,tp );
	close(sckt);
    	return 0;
}

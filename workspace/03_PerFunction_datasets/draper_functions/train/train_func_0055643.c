getPortRange()
{

    char *first;
	char *last;


	first = getenv("DCACHE_CBPORT");
	if( first != NULL ) {
		last = strchr(first, ':');
		if( last == NULL ) {
			callBackPort = atoi(first);
			callBackPortRange = 1;
		}else{

			first = xstrndup(first, last - first);
			callBackPort = atoi(first);
			free(first);
			++last;
			callBackPortRange = atoi(last) - callBackPort;
			if( callBackPortRange <=0 ) callBackPortRange = 1;
		}

		dc_debug(DC_INFO, "callback port = %d:%d",callBackPort,  callBackPort + callBackPortRange );
	}
}

speedportReconnect( struct sProfile *psProfile ) {
	struct sUrlHandler *psHandler;
	gchar anUrl[ BUF_SIZE ];
	gint nError = -1;

	if( routerLogin( psProfile ) != 0 ) {
		return nError;
	}


	snprintf( anUrl, sizeof( anUrl ), "%s%s/cgi-bin/webcm", getRouterProtocol( psProfile ), routerGetHost( psProfile ) );
	psHandler = urlHandler( anUrl, getRouterPort( psProfile ) );
	setPostData( psHandler,	"connection0:settings/cmd_disconnect=1" );
	nError = readUrl( psHandler, psProfile );
	freeHandler( psHandler );


	snprintf( anUrl, sizeof( anUrl ), "%s%s/cgi-bin/webcm", getRouterProtocol( psProfile ), routerGetHost( psProfile ) );
	psHandler = urlHandler( anUrl, getRouterPort( psProfile ) );
	setPostData( psHandler,	"connection0:settings/cmd_connect=1" );
	nError = readUrl( psHandler, psProfile );
	freeHandler( psHandler );

	return nError;
}

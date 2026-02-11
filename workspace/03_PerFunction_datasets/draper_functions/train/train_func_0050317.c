speedportLogin( struct sProfile *psProfile ) {
	struct sUrlHandler *psHandler;
	gint nError;
	gchar anUrl[ BUF_SIZE ];
	const gchar *pnPassword = routerGetPassword( psProfile );

	if ( pnPassword == NULL ) {
		return -1;
	}

	snprintf( anUrl, sizeof( anUrl ), "%s%s/cgi-bin/webcm", getRouterProtocol( psProfile ), routerGetHost( psProfile ) );
	psHandler = urlHandler( anUrl, getRouterPort( psProfile ) );
	if ( psProfile -> sRouterInfo.nSubType == 1 ) {
		setPostData( psHandler, "&getpage=../html/hcti_startseite.htm&login:command/password=%s", pnPassword );
	} else {
		setPostData( psHandler, "&login:command/password=%s", pnPassword );
	}
	nError = readUrl( psHandler, psProfile );
	if ( nError != 0 ) {
		Debug( KERN_DEBUG, "No data\n" );
		freeHandler( psHandler );
		return nError;
	}
	saveDebugData( "speedport_login.html", psHandler -> pnData, psHandler -> nSize );

	if ( strstr( psHandler -> pnData, "<div id=c_errtitel>" ) ) {
		nError = -1;
		Debug( KERN_WARNING, "Login failed, wrong password!\n" );
		ShowError( TRUE, _( "Login failed" ), _( "Wrong password or already logged in!" ) );
	} else {
		nError = 0;
		Debug( KERN_DEBUG, "Login successful!\n" );
	}
	freeHandler( psHandler );

	return nError;
}

fritzBoxDetect( struct sProfile *psProfile ) {
	struct sUrlHandler *psHandler;
	gint nError;
	gchar anUrl[ BUF_SIZE ];

	Debug( KERN_INFO, "Starting detection\n" );

	snprintf( anUrl, sizeof( anUrl ), "%s/cgi-bin/webcm", routerGetHost( psProfile ) );
	psHandler = urlHandler( anUrl, 80 );
	nError = readUrl( psHandler, psProfile );
	if ( nError != 0 ) {
		freeHandler( psHandler );
		Debug( KERN_DEBUG, "No FRITZ!Box\n" );
		return nError;
	}

	if ( g_strcasestr( psHandler -> pnData, "fritz!box" ) ) {
		nError = 0;
		Debug( KERN_DEBUG, "FRITZ!Box found!\n" );
	} else {
		nError = 1;
		Debug( KERN_DEBUG, "No FRITZ!Box - no indication in site found\n" );
	}
	freeHandler( psHandler );

	return nError;
}

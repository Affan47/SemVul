fritzBoxCallNumber( struct sProfile *psProfile, const gchar *pnNumber, int nType ) {
	struct sUrlHandler *psHandler = NULL;
	gchar anUrl[ BUF_SIZE ];
	gint nPort = 0;
	gint nError = -1;

	Debug( KERN_DEBUG, "Call number...\n" );

	nPort = fritzBoxGetPortNumber( nType );
	if ( nPort == -1 ) {
		return nError;
	}

	nError = routerLogin( psProfile );
	if ( nError == 0 ) {
		gchar *pnTmp1 = urlEncode( pnNumber );

		snprintf( anUrl, sizeof( anUrl ), "%s/cgi-bin/webcm", routerGetHost( psProfile ) );
		psHandler = urlHandler( anUrl, 80 );

		Debug( KERN_INFO, "pnTmp1: '%s'\n", pnTmp1 );
		setPostData( psHandler,
					"&telcfg:settings/UseClickToDial=1&telcfg:settings/DialPort=%d&telcfg:command/Dial=%s&sid=%s", nPort, pnTmp1, psProfile -> sRouterInfo.pnSessionId );
		nError = readUrl( psHandler, psProfile );
		g_free( pnTmp1 );

		freeHandler( psHandler );
		routerLogout( psProfile );
	}

	return nError;
}

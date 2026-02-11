parseCsvFile( const char *pnName, char *pnProfileName ) {
	gchar *pnData = loadData( ( char * ) pnName, NULL );
	int nError = -1;

	if ( pnData == NULL ) {
		return nError;
	}

	nError = parseCsvData( pnData, pnProfileName );
	g_free( pnData );

	return nError;
}

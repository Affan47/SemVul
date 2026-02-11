SaveFilters( void ) {
	xmlnode *node;
	char *pnData;

	node = filtersToXmlnode();
	pnData = xmlnode_to_formatted_str( node, NULL );
	if ( pnData != NULL ) {
		int nFile, nResult;
		char *pnFile = g_build_filename( getUserDir(), "filters.xml", NULL );

		nFile = open( pnFile, O_RDWR | O_CREAT | O_TRUNC, 0600 );
		if ( nFile > 0 ) {
			nResult = write( nFile, pnData, strlen( pnData ) );
			if ( nResult != strlen( pnData ) ) {
				Debug( KERN_WARNING, "Could not save file %s\n", pnFile );
			}
			close( nFile );
		}
	}
	g_free( pnData );
	xmlnode_free( node );
}

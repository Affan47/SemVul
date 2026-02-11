xmlnode_insert_data( xmlnode *psNode, const char *pnData, gssize nSize ) {
	xmlnode *psChild;
	gsize nRealSize;

	g_return_if_fail( psNode != NULL );
	g_return_if_fail( pnData != NULL );
	g_return_if_fail( nSize != 0 );

	if ( nSize == -1 ) {
		nRealSize = strlen( pnData );
	} else {
 		nRealSize = nSize;
	}

	psChild = new_node( NULL, XMLNODE_TYPE_DATA );

	psChild -> pnData = g_memdup( pnData, nRealSize );
	psChild -> nDataSize = nRealSize;

	xmlnode_insert_child( psNode, psChild );
}

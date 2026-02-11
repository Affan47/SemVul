addDtmfAction( xmlnode *psNode ) {
	struct sDtmf *psDtmf = NULL;
	xmlnode *psChild = NULL;
	gchar *pnName = NULL;
	gchar *pnCaller = NULL;
	gchar *pnCalled = NULL;
	gchar *pnCode = NULL;
	gchar *pnExec = NULL;

	psChild = xmlnode_get_child( psNode, "name" );
	if ( psChild != NULL ) {
		pnName = xmlnode_get_data( psChild );

		psChild = xmlnode_get_child( psNode, "caller" );
		if ( psChild != NULL ) {
			pnCaller = xmlnode_get_data( psChild );

			psChild = xmlnode_get_child( psNode, "called" );
			if ( psChild != NULL ) {
				pnCalled = xmlnode_get_data( psChild );

				psChild = xmlnode_get_child( psNode, "code" );
				if ( psChild != NULL ) {
					pnCode = xmlnode_get_data( psChild );

					psChild = xmlnode_get_child( psNode, "exec" );
					if ( psChild != NULL ) {
						pnExec = xmlnode_get_data( psChild );

						psDtmf = g_malloc0( sizeof( struct sDtmf ) );

						if ( psDtmf != NULL ) {

							psDtmf -> pnName = g_strdup( pnName );
							psDtmf -> pnCaller = g_strdup( pnCaller );
							psDtmf -> pnCalled = g_strdup( pnCalled );
							psDtmf -> pnCode = g_strdup( pnCode );
							psDtmf -> pnExecute = g_strdup( pnExec );
							psDtmfActionList = g_list_prepend( psDtmfActionList, psDtmf );
						}

						g_free( pnExec );
					}

					g_free( pnCode );
				}

				g_free( pnCalled );
			}

			g_free( pnCaller );
		}

		g_free( pnName );
	}
}

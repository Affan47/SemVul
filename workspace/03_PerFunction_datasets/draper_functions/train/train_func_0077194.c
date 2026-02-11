removeDtmfAction( const gchar *pnName ) {
	struct sDtmf *psDtmf = findDtmfAction( pnName );

	if ( psDtmf != NULL ) {
		psDtmfActionList = g_list_remove( psDtmfActionList, psDtmf );
	}
}

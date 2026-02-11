findCardData( GList *psList, gchar *pnHeader, gchar *pnOption ) {
	GList *psTmp = NULL;
	struct sCardData *psData = NULL;

	for ( psTmp = psList; psTmp != NULL && psTmp -> data != NULL; psTmp = psTmp -> next ) {
		psData = psTmp -> data;

		if( strcmp( psData -> pnHeader, pnHeader ) == 0 ) {
			if ( pnOption != NULL && psData -> pnOptions != NULL && strstr( psData -> pnOptions, pnOption ) ) {
				return psData;
			}
		}
	}

	return NULL;
}

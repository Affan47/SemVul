getLookupList( const gchar *pnCountryCode ) {
	GList *psList = NULL;


	if ( pnCountryCode == NULL ) {
		return psLookupList;
	}

	if ( psLookupTable == NULL ) {
		return NULL;
	}


	psList = g_hash_table_lookup( psLookupTable, ( gpointer ) atol( pnCountryCode ) );

	return psList;
}

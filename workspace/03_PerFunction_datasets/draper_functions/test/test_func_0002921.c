parseTables( void ) {
	GHashTable *psTables = psTableScopeMap;

	if ( psTables != NULL ) {
		GHashTableIter sIter1;
		gpointer pKey1, pValue1;

		g_hash_table_iter_init( &sIter1, psTables );
		while ( g_hash_table_iter_next( &sIter1, &pKey1, &pValue1 ) )  {
			if ( GPOINTER_TO_INT( pKey1 ) == 0 ) {

			}

			GHashTable *psRows = pValue1;
			if ( psRows != NULL ) {
				GHashTableIter sIter2;
				gpointer pKey2, pValue2;

				g_hash_table_iter_init( &sIter2, psRows );
				while ( g_hash_table_iter_next( &sIter2, &pKey2, &pValue2 ) )  {
					if ( GPOINTER_TO_INT( pKey2 ) == 0 ) {

					}

					GHashTable *psRows2 = pValue2;
					if ( psRows2 != NULL ) {
						GHashTableIter sIter3;
						gpointer pKey3, pValue3;

						g_hash_table_iter_init( &sIter3, psRows2 );
						while ( g_hash_table_iter_next( &sIter3, &pKey3, &pValue3 ) )  {
							if ( GPOINTER_TO_INT( pKey3 ) == 0 ) {

							}

							GHashTable *psRows3 = pValue3;
							if ( psRows3 != NULL ) {
								GHashTableIter sIter4;
								gpointer pKey4, pValue4;

								g_hash_table_iter_init( &sIter4, psRows3 );
								while ( g_hash_table_iter_next( &sIter4, &pKey4, &pValue4 ) )  {
									if ( GPOINTER_TO_INT( pKey4 ) == 0 ) {

									}

									GHashTable *psRows4 = pValue4;
									if ( psRows4 != NULL ) {
										parsePerson( psRows4, pKey4 );
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

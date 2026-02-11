ldif_hash_add_list( GHashTable *table, GSList *list ) {
	GSList *node = list;


	while( node ) {
		gchar *tag = node->data;
		if( ! g_hash_table_lookup( table, tag ) ) {
			Ldif_FieldRec *rec = NULL;
			gchar *key = g_utf8_strdown( tag, -1 );

			rec = ldif_create_fieldrec( tag );
			if( g_utf8_collate( key, LDIF_TAG_DN ) == 0 ) {
				rec->reserved = rec->selected = TRUE;
				rec->userName = g_strdup( "dn" );
			}
			else if( g_utf8_collate( key, g_utf8_strdown( LDIF_TAG_COMMONNAME, -1 ) ) == 0 ) {
				rec->reserved = rec->selected = TRUE;
				rec->userName = g_strdup( _( "Display Name" ) );
			}
			else if( g_utf8_collate( key, g_utf8_strdown( LDIF_TAG_FIRSTNAME, -1 ) ) == 0 ) {
				rec->reserved = rec->selected = TRUE;
				rec->userName = g_strdup( _( "First Name" ) );
			}
			else if( g_utf8_collate( key, g_utf8_strdown( LDIF_TAG_LASTNAME, -1 ) ) == 0 ) {
				rec->reserved = rec->selected = TRUE;
				rec->userName = g_strdup( _( "Last Name" ) );
			}
			else if( g_utf8_collate( key, g_utf8_strdown( LDIF_TAG_NICKNAME, -1 ) ) == 0 ) {
				rec->reserved = rec->selected = TRUE;
				rec->userName = g_strdup( _( "Nick Name" ) );
			}
			else if( g_utf8_collate( key, g_utf8_strdown( LDIF_TAG_EMAIL, -1 ) ) == 0 ) {
				rec->reserved = rec->selected = TRUE;
				rec->userName = g_strdup( _( "Email Address" ) );
			}
			g_hash_table_insert( table, key, rec );
		}
		node = g_slist_next( node );
	}
}

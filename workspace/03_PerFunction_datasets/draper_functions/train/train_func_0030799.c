createAction( const gchar *pnName ) {
	struct sAction *psAction = NULL;

	psAction = g_malloc0( sizeof( struct sAction ) );

	if ( psAction != NULL ) {
		psAction -> pnName = g_strdup( pnName );
		psActionList = g_list_prepend( psActionList, psAction );
	} else {
		Debug( KERN_WARNING, "Could not add '%s'\n", pnName );
	}

	return psAction;
}

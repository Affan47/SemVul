browse_idle( gpointer data ) {
	GList *node;
	NameValuePair *nvp;
	gchar *text[N_COLS];


	pthread_mutex_lock( & _browseMutex_ );
	if( _displayQueue_ ) {
		node = _displayQueue_;
		while( node ) {

			nvp = ( NameValuePair * ) node->data;
			text[COL_NAME]  = nvp->name;
			text[COL_VALUE] = nvp->value;
			debug_print("Adding row to list: %s->%s\n",
						nvp->name?nvp->name:"null",
						nvp->value?nvp->value:"null");
			gtk_cmclist_append(
				GTK_CMCLIST(browseldap_dlg.list_entry), text );


			ldapqry_free_name_value( nvp );
			node->data = NULL;
			node = g_list_next( node );
		}
		g_list_free( _displayQueue_ );
		_displayQueue_ = NULL;
	}
	pthread_mutex_unlock( & _browseMutex_ );

	if( _searchComplete_ ) {

		if( _browseIdleID_ != 0 ) {
			g_source_remove( _browseIdleID_ );
			_browseIdleID_ = 0;
			gtk_cmclist_select_row(
				GTK_CMCLIST( browseldap_dlg.list_entry ), 0, 0 );
		}
	}

	return TRUE;
}

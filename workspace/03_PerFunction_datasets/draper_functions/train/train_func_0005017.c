selectedToggled( GtkCellRendererToggle *psToggle, gchar *pnPathStr, gpointer pUserData ) {
	GtkTreeModel *psModel = gtk_tree_view_get_model( GTK_TREE_VIEW( pUserData ) );
	GtkTreeIter sIter;
	GtkTreePath *psPath = gtk_tree_path_new_from_string( pnPathStr );
	gchar *pnNumber;
	gboolean bDial;
	gint nType = 0;

	gtk_tree_model_get_iter( psModel, &sIter, psPath );
	gtk_tree_model_get( psModel, &sIter, 0, &bDial, 2, &pnNumber, -1 );

	nType = routerGetFonType( getActiveProfile(), pnNumber );
	if ( nType != -1 ) {
		nType = ( 1 << ( nType + ACTION_TYPE_MAX ) );
		if ( bDial == TRUE ) {
			nActionMsnFlags &= ~nType;
		} else {
			nActionMsnFlags |= nType;
		}
		Debug( KERN_DEBUG, "%d %x\n", nType, nActionMsnFlags );

		bDial ^= 1;

		gtk_list_store_set( GTK_LIST_STORE( psModel ), &sIter, 0, bDial, -1 );
	}

	gtk_tree_path_free( psPath );
}

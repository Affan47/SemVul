actionsEdit( GtkWidget *psButton, gpointer pUserData ) {
	GtkTreeIter sSelectedIter;
	GtkTreeModel *psModel;
	GtkTreeSelection *psSelection = gtk_tree_view_get_selection( pUserData );
	struct sAction *psAction = NULL;

	if ( gtk_tree_selection_get_selected( psSelection, &psModel, &sSelectedIter ) ) {
		GValue sName = { 0 };

		gtk_tree_model_get_value( psModel, &sSelectedIter, 0, &sName );

		psAction = findAction( g_value_get_string( &sName ) );

		g_value_unset( &sName );

		if ( psAction != NULL ) {
			actionsAdd( NULL, psAction );
		}
	}
}

_setActive( gint active )
{
    if ( active != _active || (_activeUnit == 0) ) {
        gint oldActive = _active;

        GtkTreeIter iter;
        gboolean found = gtk_tree_model_iter_nth_child( GTK_TREE_MODEL(_store), &iter, NULL, oldActive );
        if ( found ) {
            SPUnit* unit = 0;
            gtk_tree_model_get( GTK_TREE_MODEL(_store), &iter, COLUMN_SPUNIT, &unit, -1 );

            found = gtk_tree_model_iter_nth_child( GTK_TREE_MODEL(_store), &iter, NULL, active );
            if ( found ) {
                SPUnit* newUnit = 0;
                gtk_tree_model_get( GTK_TREE_MODEL(_store), &iter, COLUMN_SPUNIT, &newUnit, -1 );
                _activeUnit = newUnit;

                if ( _adjList ) {
                    _fixupAdjustments( unit, newUnit );
                }

            } else {
                g_warning("Did not find new unit");
            }
        } else {
            g_warning("Did not find old unit");
        }

        _active = active;

        for ( GSList* cur = _actionList; cur; cur = g_slist_next(cur) ) {
            if ( IS_EGE_SELECT_ONE_ACTION( cur->data ) ) {
                EgeSelectOneAction* act = EGE_SELECT_ONE_ACTION( cur->data );
                ege_select_one_action_set_active( act, active );
            }
        }
    }
}

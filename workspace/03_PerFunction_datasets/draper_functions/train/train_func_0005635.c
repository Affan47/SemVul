insert_reinf_unit( Unit *unit, int player, int scenario ) {

    {
        Unit *item;
        int i = 0;
        list_reset( reinf[player][scenario] );
        for (i = 0; (item = list_next( reinf[player][scenario] )); i++) {
            if ( unit->nation == item->nation ) break;
        }

        list_insert( reinf[player][scenario], unit, i );
    }
}

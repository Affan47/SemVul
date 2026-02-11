map_supplied_by_depot( int mx, int my, Unit *unit )
{
    int i;
    if ( map_is_allied_depot( &map[mx][my], unit ) )
        return 1;
    for ( i = 0; i < 6; i++ )
        if ( map_is_allied_depot( map_get_close_hex( mx, my, i ), unit ) )
            return 1;
    return 0;
}

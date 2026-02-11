engine_focus( int x, int y, int use_sc )
{
    int new_x, new_y;
    if ( x <= map_x + 1 || y <= map_y + 1 || x >= map_x + map_sw - 1 - 2 || y >= map_y + map_sh - 1 - 2 ) {
        new_x = x - ( map_sw >> 1 );
        new_y = y - ( map_sh >> 1 );
        if ( new_x & 1 ) new_x++;
        if ( new_y & 1 ) new_y++;
        engine_goto_xy( new_x, new_y );
        if ( !use_sc ) sc_type = SC_NONE;
        return 1;
    }
    return 0;
}

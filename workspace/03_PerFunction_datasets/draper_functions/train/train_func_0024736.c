map_update_spot_mask( Unit *unit, int *enemy_spotted )
{
    int x, y;
    *enemy_spotted = 0;
    if ( player_is_ally( cur_player, unit->player ) ) {

        map_get_unit_spot_mask( unit );
        for ( x = 0; x < map_w; x++ )
            for ( y = 0; y < map_h; y++ )
                if ( mask[x][y].aux ) {


                    if ( !mask[x][y].spot ) {
                        if ( map[x][y].g_unit && !player_is_ally( unit->player, map[x][y].g_unit->player ) )
                            *enemy_spotted = 1;
                        if ( map[x][y].a_unit && !player_is_ally( unit->player, map[x][y].a_unit->player ) )
                            *enemy_spotted = 1;
                    }
                    mask[x][y].spot = 1;
                }
    }
}

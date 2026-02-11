subcond_check( VSubCond *cond )
{
    Unit *unit;
    int x,y,count;
    if ( cond == 0 ) return 0;
    switch ( cond->type ) {
        case VSUBCOND_CTRL_ALL_HEXES:
            for ( x = 0; x < map_w; x++ )
                for ( y = 0; y < map_h; y++ )
                    if ( map[x][y].player && map[x][y].obj )
                        if ( !player_is_ally( cond->player, map[x][y].player ) )
                            return 0;
            return 1;
        case VSUBCOND_CTRL_HEX:
            if ( map[cond->x][cond->y].player )
                if ( player_is_ally( cond->player, map[cond->x][cond->y].player ) )
                    return 1;
            return 0;
        case VSUBCOND_TURNS_LEFT:
            if ( scen_info->turn_limit - turn > cond->count )
                return 1;
            else
                return 0;
        case VSUBCOND_CTRL_HEX_NUM:
            count = 0;
            for ( x = 0; x < map_w; x++ )
                for ( y = 0; y < map_h; y++ )
                    if ( map[x][y].player && map[x][y].obj )
                        if ( player_is_ally( cond->player, map[x][y].player ) )
                            count++;
            if ( count >= cond->count )
                return 1;
            return 0;
        case VSUBCOND_UNITS_KILLED:


            list_reset( units );
            while ( ( unit = list_next( units ) ) )
                if ( !unit->killed && !player_is_ally( cond->player, unit->player ) )
                    if ( unit->tag[0] != 0 && STRCMP( unit->tag, cond->tag ) )
                        return 0;
            return 1;
        case VSUBCOND_UNITS_SAVED:


            list_reset( units ); count = 0;
            while ( ( unit = list_next( units ) ) )
                if ( player_is_ally( cond->player, unit->player ) )
                    if ( unit->tag[0] != 0 && STRCMP( unit->tag, cond->tag ) )
                        count++;
            if ( count == cond->count )
                return 1;
            return 0;
    }
    return 0;
}

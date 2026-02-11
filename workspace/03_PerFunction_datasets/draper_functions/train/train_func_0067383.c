map_check_unit_debark( Unit *unit, int x, int y, int type, int init )
{
    if ( x < 0 || y < 0 || x >= map_w || y >= map_h ) return 0;
    if ( type == EMBARK_SEA ) {
        if ( unit->embark != EMBARK_SEA ) return 0;
        if ( !init && map[x][y].g_unit ) return 0;
        if ( !init && !unit->unused ) return 0;
        if ( !init && terrain_get_mov( map[x][y].terrain, unit->prop.mov_type, cur_weather ) == 0 ) return 0;
        return 1;
    }
    if ( type == EMBARK_AIR ) {
        if ( unit->embark != EMBARK_AIR ) return 0;
        if ( !init && map[x][y].g_unit ) return 0;
        if ( !init && !unit->unused ) return 0;
        if ( !init && terrain_get_mov( map[x][y].terrain, unit->prop.mov_type, cur_weather ) == 0 ) return 0;
        if ( !init && !( map[x][y].terrain->flags[cur_weather] & SUPPLY_AIR ) && !( unit->prop.flags & PARACHUTE ) )
            return 0;
        return 1;
    }
    return 0;
}

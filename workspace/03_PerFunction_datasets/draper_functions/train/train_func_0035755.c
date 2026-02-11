map_add_unit_spot_mask( Unit *unit )
{
    int i, next_x, next_y;
    if ( unit->x < 0 || unit->y < 0 || unit->x >= map_w || unit->y >= map_h ) return;
    mask[unit->x][unit->y].aux = unit->sel_prop->spt;
    for ( i = 0; i < 6; i++ )
        if ( get_close_hex_pos( unit->x, unit->y, i, &next_x, &next_y ) )
            map_add_unit_spot_mask_rec( unit, next_x, next_y, unit->sel_prop->spt );
}

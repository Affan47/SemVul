fighter_move(piece_info_t *obj)
{
    loc_t new_loc;

    new_loc = find_attack (obj->loc, fighter_attack, ".+");
    if (new_loc != obj->loc) {
	attack (obj, new_loc);
	return;
    }

    if (obj->range <= find_nearest_city (obj->loc, COMP, &new_loc) + 2) {
	if (new_loc != obj->loc)
	    new_loc = vmap_find_dest (path_map, comp_map, obj->loc,
				      new_loc, COMP, T_AIR);
    }
    else new_loc = obj->loc;

    if (new_loc == obj->loc) {
	new_loc = vmap_find_aobj (path_map, comp_map, obj->loc,
				  &fighter_fight);
    }
    move_objective (obj, path_map, new_loc, " ");
}

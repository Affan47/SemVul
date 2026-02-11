cpiece_move(piece_info_t *obj)
{
    void move1();

    bool changed_loc;
    int max_hits;
    loc_t saved_loc;
    city_info_t *cityp;

    if (obj->type == SATELLITE) {
	move_sat (obj);
	return;
    }

    obj->moved = 0;
    changed_loc = false;
    max_hits = piece_attr[obj->type].max_hits;

    if (obj->type == FIGHTER) {
	cityp = find_city (obj->loc);
	if (cityp != NULL) obj->range = piece_attr[FIGHTER].range;
    }

    while (obj->moved < obj_moves (obj)) {
	saved_loc = obj->loc;
	move1 (obj);
	if (saved_loc != obj->loc) changed_loc = true;

	if (obj->type == FIGHTER && obj->hits > 0) {
	    if (comp_map[obj->loc].contents == 'X')
		obj->moved = piece_attr[FIGHTER].speed;
	    else if (obj->range == 0) {
		pdebug ("Fighter at %d crashed and burned\n", loc_disp(obj->loc));
		ksend ("Fighter at %d crashed and burned\n", loc_disp(obj->loc));
		kill_obj (obj, obj->loc);
	    }
	}
    }

    if (obj->hits > 0
	&& !changed_loc
	&& obj->type != ARMY && obj->type != FIGHTER
	&& obj->hits != max_hits
	&& comp_map[obj->loc].contents == 'X')
	obj->hits++;
}

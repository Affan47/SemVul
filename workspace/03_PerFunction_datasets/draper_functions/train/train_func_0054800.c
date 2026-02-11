do_light_sources(cs_rows)
    char **cs_rows;
{
    int x, y, min_x, max_x, max_y, offset;
    char *limits;
    short at_hero_range = 0;
    light_source *ls;
    char *row;

    for (ls = light_base; ls; ls = ls->next) {
	ls->flags &= ~LSF_SHOW;


	if (ls->type == LS_OBJECT) {
	    if (get_obj_location((struct obj *) ls->id, &ls->x, &ls->y, 0))
		ls->flags |= LSF_SHOW;
	} else if (ls->type == LS_MONSTER) {
	    if (get_mon_location((struct monst *) ls->id, &ls->x, &ls->y, 0))
		ls->flags |= LSF_SHOW;
	}


	if (ls->x == u.ux && ls->y == u.uy) {
	    if (at_hero_range >= ls->range)
		ls->flags &= ~LSF_SHOW;
	    else
		at_hero_range = ls->range;
	}

	if (ls->flags & LSF_SHOW) {


	    limits = circle_ptr(ls->range);
	    if ((max_y = (ls->y + ls->range)) >= ROWNO) max_y = ROWNO-1;
	    if ((y = (ls->y - ls->range)) < 0) y = 0;
	    for (; y <= max_y; y++) {
		row = cs_rows[y];
		offset = limits[abs(y - ls->y)];
		if ((min_x = (ls->x - offset)) < 0) min_x = 0;
		if ((max_x = (ls->x + offset)) >= COLNO) max_x = COLNO-1;

		if (ls->x == u.ux && ls->y == u.uy) {


		    for (x = min_x; x <= max_x; x++)
			if (row[x] & COULD_SEE)
			    row[x] |= TEMP_LIT;
		} else {
		    for (x = min_x; x <= max_x; x++)
			if ((ls->x == x && ls->y == y)
				|| clear_path((int)ls->x, (int) ls->y, x, y))
			    row[x] |= TEMP_LIT;
		}
	    }
	}
    }
}

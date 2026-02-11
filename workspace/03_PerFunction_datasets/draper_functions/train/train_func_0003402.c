Vect_select_lines_by_polygon(struct Map_info *Map, struct line_pnts *Polygon,
			     int nisles, struct line_pnts **Isles, int type,
			     struct ilist *List)
{
    int i;
    BOUND_BOX box;
    static struct line_pnts *LPoints = NULL;
    static struct ilist *LocList = NULL;


    G_debug(3, "Vect_select_lines_by_polygon() nisles = %d", nisles);

    List->n_values = 0;
    if (!LPoints)
	LPoints = Vect_new_line_struct();
    if (!LocList)
	LocList = Vect_new_list();


    dig_line_box(Polygon, &box);
    box.T = PORT_DOUBLE_MAX;
    box.B = -PORT_DOUBLE_MAX;
    Vect_select_lines_by_box(Map, &box, type, LocList);
    G_debug(3, "  %d lines selected by box", LocList->n_values);


    for (i = 0; i < LocList->n_values; i++) {
	int j, line, intersect = 0;

	line = LocList->value[i];

	Vect_read_line(Map, LPoints, NULL, line);


	for (j = 0; j < LPoints->n_points; j++) {
	    if (Vect_point_in_poly(LPoints->x[j], LPoints->y[j], Polygon) >= 1) {
		int k, inisle = 0;

		for (k = 0; k < nisles; k++) {
		    if (Vect_point_in_poly(LPoints->x[j], LPoints->y[j], Isles[k]) >= 1) {
			inisle = 1;
			break;
		    }
		}

		if (!inisle) {
		    intersect = 1;
		    break;
		}
	    }
	}
	if (intersect) {
	    dig_list_add(List, line);
	    continue;
	}


	if (Vect_line_check_intersection(LPoints, Polygon, 0)) {
	    dig_list_add(List, line);
	    continue;
	}


	for (j = 0; j < nisles; j++) {
	    if (Vect_line_check_intersection(LPoints, Isles[j], 0)) {
		intersect = 1;
		break;
	    }
	}
	if (intersect) {
	    dig_list_add(List, line);
	}
    }

    G_debug(4, "  %d lines selected by polygon", List->n_values);

    return List->n_values;
}

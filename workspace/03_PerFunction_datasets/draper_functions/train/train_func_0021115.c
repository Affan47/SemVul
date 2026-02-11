sel_by_bbox(struct Map_info *Map,
		int type, double x1, double y1, double x2, double y2,
		struct ilist *List)
{
    BOUND_BOX bbox;

    struct ilist *List_tmp;

    if (first_selection) {
	List_tmp = List;
	first_selection = 0;
    }
    else {
	List_tmp = Vect_new_list();
    }


    bbox.N = y1 < y2 ? y2 : y1;
    bbox.S = y1 < y2 ? y1 : y2;
    bbox.W = x1 < x2 ? x1 : x2;
    bbox.E = x1 < x2 ? x2 : x1;
    bbox.T = PORT_DOUBLE_MAX;
    bbox.B = -PORT_DOUBLE_MAX;

    Vect_select_lines_by_box(Map, &bbox, type, List_tmp);

    G_debug(1, "  %d lines selected (by bbox)", List_tmp->n_values);


    if (List_tmp != List) {
	merge_lists(List, List_tmp);
	Vect_destroy_list(List_tmp);
    }

    return List->n_values;
}

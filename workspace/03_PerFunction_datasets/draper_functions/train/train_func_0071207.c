Vedit_modify_cats(struct Map_info *Map, struct ilist *List,
		      int layer, int del, struct cat_list *Clist)
{
    int i, j;
    struct line_cats *Cats;
    struct line_pnts *Points;
    int line, type, cat;
    int nlines_modified, rewrite;


    if (Clist->n_ranges <= 0) {
	return 0;
    }

    nlines_modified = 0;

    Cats = Vect_new_cats_struct();
    Points = Vect_new_line_struct();


    for (i = 0; i < List->n_values; i++) {
	line = List->value[i];
	type = Vect_read_line(Map, Points, Cats, line);

	if (!Vect_line_alive(Map, line))
	    continue;

	rewrite = 0;
	for (j = 0; j < Clist->n_ranges; j++) {
	    for (cat = Clist->min[j]; cat <= Clist->max[j]; cat++) {

		if (!del) {
		    if (Vect_cat_set(Cats, layer, cat) < 1) {
			G_warning(_("Unable to set category %d for (feature id %d)"),
				  cat, line);
		    }
		    else {
			rewrite = 1;
		    }
		}
		else {
		    if (Vect_field_cat_del(Cats, layer, cat) == 1) {
			rewrite = 1;
		    }
		}
	    }
	}

	if (rewrite == 0)
	    continue;

	if (Vect_rewrite_line(Map, line, type, Points, Cats) < 0) {
	    return -1;
	}

	nlines_modified++;

    }


    Vect_destroy_line_struct(Points);
    Vect_destroy_cats_struct(Cats);

    return nlines_modified;
}

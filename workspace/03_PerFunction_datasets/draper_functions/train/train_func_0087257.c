parametric_3dfixup(struct surface_points *start_plot, int *plot_num)
{
    struct surface_points *xp, *new_list, *free_list = NULL;
    struct surface_points **last_pointer = &new_list;
    int i, surface;


    new_list = xp = start_plot;
    for (surface = 0; surface < *plot_num; surface++) {
	if (xp->plot_type == FUNC3D) {
	    struct surface_points *yp = xp->next_sp;
	    struct surface_points *zp = yp->next_sp;


	    struct iso_curve *xicrvs = xp->iso_crvs;
	    struct iso_curve *yicrvs = yp->iso_crvs;
	    struct iso_curve *zicrvs = zp->iso_crvs;

	    (*plot_num) -= 2;

	    assert(INRANGE < OUTRANGE && OUTRANGE < UNDEFINED);

	    while (zicrvs) {
		struct coordinate GPHUGE *xpoints = xicrvs->points;
		struct coordinate GPHUGE *ypoints = yicrvs->points;
		struct coordinate GPHUGE *zpoints = zicrvs->points;

		for (i = 0; i < zicrvs->p_count; ++i) {
		    zpoints[i].x = xpoints[i].z;
		    zpoints[i].y = ypoints[i].z;
		    if (zpoints[i].type < xpoints[i].type)
			zpoints[i].type = xpoints[i].type;
		    if (zpoints[i].type < ypoints[i].type)
			zpoints[i].type = ypoints[i].type;

		}
		xicrvs = xicrvs->next;
		yicrvs = yicrvs->next;
		zicrvs = zicrvs->next;
	    }


	    assert(xp->next_sp == yp);
	    yp->next_sp = free_list;
	    free_list = xp;


	    *last_pointer = zp;
	    last_pointer = &(zp->next_sp);
	    xp = zp->next_sp;
	} else {
	    assert(*last_pointer == xp);
	    last_pointer = &(xp->next_sp);
	    xp = xp->next_sp;
	}
    }


    *last_pointer = free_list;
    first_3dplot = new_list;
}

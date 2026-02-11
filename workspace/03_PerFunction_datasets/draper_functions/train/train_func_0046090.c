plot_fsteps(struct curve_points *plot)
{
    int i;
    int x=0, y=0;
    struct termentry *t = term;
    enum coord_type prev = UNDEFINED;
    double ex, ey;
    double lx[2], ly[2];
    int xprev, yprev;

    for (i = 0; i < plot->p_count; i++) {
	xprev = x; yprev = y;

	switch (plot->points[i].type) {
	case INRANGE:
		x = map_x(plot->points[i].x);
		y = map_y(plot->points[i].y);

		if (prev == INRANGE) {
		    (*t->vector) (xprev, y);
		    (*t->vector) (x, y);
		} else if (prev == OUTRANGE) {

		    if (clip_lines1) {
			edge_intersect_fsteps(plot->points, i, &ex, &ey);
			xprev = map_x(ex);
			yprev = map_y(ey);
			(*t->move) (xprev, yprev);
			(*t->vector) (xprev, y);
			(*t->vector) (x, y);
		    }
		}

		(*t->move)(x, y);
		break;

	case OUTRANGE:
		if (prev == INRANGE) {

		    if (clip_lines1) {
			edge_intersect_fsteps(plot->points, i, &ex, &ey);
			x = map_x(ex);  y = map_y(ey);
			(*t->vector) (xprev, y);
			(*t->vector) (x, y);
		    }
		} else if (prev == OUTRANGE) {

		    if (clip_lines2) {
			if (two_edge_intersect_fsteps(plot->points, i, lx, ly)) {
			    xprev = map_x(lx[0]);
			    yprev = map_y(ly[0]);
			    x = map_x(lx[1]);
			    y = map_y(ly[1]);
			    (*t->move) (xprev, yprev);
			    (*t->vector) (xprev, y);
			    (*t->vector) (x, y);
			}
		    }
		}
		(*t->move)(x, y);
		break;

	default:
	case UNDEFINED:
		break;
	}
	prev = plot->points[i].type;
    }
}

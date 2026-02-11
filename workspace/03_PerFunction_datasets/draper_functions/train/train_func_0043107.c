plot_points(struct curve_points *plot)
{
    int i;
    int x, y;
    int interval = plot->lp_properties.p_interval;
    struct termentry *t = term;

    for (i = 0; i < plot->p_count; i++) {
	if ((plot->plot_style == LINESPOINTS) && (interval) && (i % interval)) {
	    continue;
	}
	if (plot->points[i].type == INRANGE) {
	    x = map_x(plot->points[i].x);
	    y = map_y(plot->points[i].y);

	    if (!clip_points
		|| (x >= plot_bounds.xleft + p_width
		    && y >= plot_bounds.ybot + p_height
		    && x <= plot_bounds.xright - p_width
		    && y <= plot_bounds.ytop - p_height)) {

		if ((plot->plot_style == POINTSTYLE || plot->plot_style == LINESPOINTS)
		&&  plot->lp_properties.p_size == PTSZ_VARIABLE)
		    (*t->pointsize)(pointsize * plot->points[i].z);


		if (plot->plot_style == LINESPOINTS && interval < 0) {
		    if (t->set_color)
			(*t->set_color)(&background_fill);
		    (*t->pointsize)(pointsize * pointintervalbox);
		    (*t->point) (x, y, 6);
		    term_apply_lp_properties(&(plot->lp_properties));
		}


		check_for_variable_color(plot, &plot->varcolor[i]);

		(*t->point) (x, y, plot->lp_properties.p_type);
	    }
	}
    }
}

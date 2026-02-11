refresh_bounds(struct curve_points *first_plot, int nplots)
{
    struct curve_points *this_plot = first_plot;
    int iplot;

    for (iplot = 0;  iplot < nplots; iplot++, this_plot = this_plot->next) {
	int i;
	struct axis *x_axis = &axis_array[this_plot->x_axis];
	struct axis *y_axis = &axis_array[this_plot->y_axis];


	if (this_plot->plot_style == IMAGE || this_plot->plot_style == RGBIMAGE) {
	    if (x_axis->set_autoscale || y_axis->set_autoscale)
		plot_image_or_update_axes(this_plot,TRUE);
	    continue;
	}

	for (i=0; i<this_plot->p_count; i++) {
	    struct coordinate GPHUGE *point = &this_plot->points[i];

	    if (point->type == UNDEFINED)
		continue;
	    else
		point->type = INRANGE;


	    if (!this_plot->noautoscale) {
		if (x_axis->set_autoscale & AUTOSCALE_MIN && point->x < x_axis->min)
		     x_axis->min = point->x;
		if (x_axis->set_autoscale & AUTOSCALE_MAX && point->x > x_axis->max)
		     x_axis->max = point->x;
	    }
	    if (!inrange(point->x, x_axis->min, x_axis->max)) {
		point->type = OUTRANGE;
		continue;
	    }
	    if (!this_plot->noautoscale) {
		if (y_axis->set_autoscale & AUTOSCALE_MIN && point->y < y_axis->min)
		     y_axis->min = point->y;
		if (y_axis->set_autoscale & AUTOSCALE_MAX && point->y > y_axis->max)
		     y_axis->max = point->y;
	    }
	    if (!inrange(point->y, y_axis->min, y_axis->max)) {
		point->type = OUTRANGE;
		continue;
	    }
	}
    }


    this_plot = first_plot;
    for (iplot = 0;  iplot < nplots; iplot++, this_plot = this_plot->next) {
	axis_checked_extend_empty_range(this_plot->x_axis, NULL);
	axis_checked_extend_empty_range(this_plot->y_axis, NULL);
    }
}

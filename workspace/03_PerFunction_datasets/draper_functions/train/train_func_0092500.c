polar_range_fiddling(struct curve_points *plot)
{
    if (axis_array[POLAR_AXIS].set_autoscale & AUTOSCALE_MAX) {
	double plotmax = GPMAX(axis_array[plot->x_axis].max, -axis_array[plot->x_axis].min);
	if ((axis_array[plot->x_axis].set_autoscale & AUTOSCALE_BOTH) == AUTOSCALE_BOTH) {
	    axis_array[plot->x_axis].max = plotmax;
	    axis_array[plot->x_axis].min = -plotmax;
	}
	if ((axis_array[plot->y_axis].set_autoscale & AUTOSCALE_BOTH) == AUTOSCALE_BOTH) {
	    axis_array[plot->y_axis].max = plotmax;
	    axis_array[plot->y_axis].min = -plotmax;
	}
    }
}

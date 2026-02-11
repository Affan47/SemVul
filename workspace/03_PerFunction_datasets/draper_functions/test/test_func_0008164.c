do_freq(
    struct curve_points *plot,
    int first_point,
    int num_points)
{
    double x, y;
    int i;
    int x_axis = plot->x_axis;
    int y_axis = plot->y_axis;
    struct coordinate GPHUGE *this;


    double ixmin, ixmax, iymin, iymax;
    double sxmin, sxmax, symin, symax;

    ixmin = sxmin = AXIS_LOG_VALUE(x_axis, X_AXIS.min);
    ixmax = sxmax = AXIS_LOG_VALUE(x_axis, X_AXIS.max);
    iymin = symin = AXIS_LOG_VALUE(y_axis, Y_AXIS.min);
    iymax = symax = AXIS_LOG_VALUE(y_axis, Y_AXIS.max);

    this = (plot->points) + first_point;

    for (i=0; i<num_points; i++) {

	x = this[i].x;
	y = this[i].y;

	this[i].type = INRANGE;

	STORE_AND_FIXUP_RANGE(this[i].x, x, this[i].type, ixmin, ixmax, X_AXIS.autoscale, NOOP, continue);
	STORE_AND_FIXUP_RANGE(this[i].y, y, this[i].type, iymin, iymax, Y_AXIS.autoscale, NOOP, NOOP);

	this[i].xlow = this[i].xhigh = this[i].x;
	this[i].ylow = this[i].yhigh = this[i].y;
	this[i].z = -1;
    }

    UPDATE_RANGE(ixmax > sxmax, X_AXIS.max, ixmax, x_axis);
    UPDATE_RANGE(ixmin < sxmin, X_AXIS.min, ixmin, x_axis);
    UPDATE_RANGE(iymax > symax, Y_AXIS.max, iymax, y_axis);
    UPDATE_RANGE(iymin < symin, Y_AXIS.min, iymin, y_axis);
}

histeps_compare(SORTFUNC_ARGS p1, SORTFUNC_ARGS p2)
{
    double x1=histeps_current_plot->points[*(int *)p1].x;
    double x2=histeps_current_plot->points[*(int *)p2].x;

    if (x1 < x2)
	return -1;
    else
	return (x1 > x2);
}

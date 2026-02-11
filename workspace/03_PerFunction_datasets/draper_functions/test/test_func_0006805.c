display_points_in_view(View * view, int in_color,
			   double *east, double *north, int *status,
			   int count)
{
    if (!view->cell.configured)
	return 1;
    while (count-- > 0) {
	if (in_color && (*status > 0))
	    R_standard_color(GREEN);
	else if (in_color && (*status == 0))
	    R_standard_color(RED);
	else
	    R_standard_color(GREY);
	status++;
	display_one_point(view, *east++, *north++);
    }

    return 0;
}

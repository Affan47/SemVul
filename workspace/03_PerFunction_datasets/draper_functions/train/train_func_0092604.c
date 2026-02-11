Vect_line_insert_point(struct line_pnts *Points, int index, double x,
		       double y, double z)
{
    register int n;

    if (index < 0 || index > Points->n_points - 1)
	G_fatal_error("%s Vect_line_insert_point()",
		      _("Index out of range in"));

    if (0 > dig_alloc_points(Points, Points->n_points + 1))
	return (-1);


    for (n = Points->n_points; n > index; n--) {
	Points->x[n] = Points->x[n - 1];
	Points->y[n] = Points->y[n - 1];
	Points->z[n] = Points->z[n - 1];
    }

    Points->x[index] = x;
    Points->y[index] = y;
    Points->z[index] = z;
    return ++(Points->n_points);
}

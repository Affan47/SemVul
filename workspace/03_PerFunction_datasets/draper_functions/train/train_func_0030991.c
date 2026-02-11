Vect_line_delete_point(struct line_pnts *Points, int index)
{
    register int n;

    if (index < 0 || index > Points->n_points - 1)
	G_fatal_error("%s Vect_line_insert_point()",
		      _("Index out of range in"));

    if (Points->n_points == 0)
	return 0;


    for (n = index; n < Points->n_points - 1; n++) {
	Points->x[n] = Points->x[n + 1];
	Points->y[n] = Points->y[n + 1];
	Points->z[n] = Points->z[n + 1];
    }

    return --(Points->n_points);
}

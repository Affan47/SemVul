douglas_peucker(struct line_pnts *Points, double thresh, int with_z)
{
    int *stack = G_malloc(sizeof(int) * Points->n_points * 2);

    if (!stack) {
	G_fatal_error(_("Out of memory"));
	return Points->n_points;
    }

    int *index = G_malloc(sizeof(int) * Points->n_points);

    if (!index) {
	G_fatal_error(_("Out of memory"));
	G_free(stack);
	return Points->n_points;
    }

    int top = 2;
    int icount = 1;
    int i;

    thresh *= thresh;

    index[0] = 0;


    stack[0] = 0;
    stack[1] = Points->n_points - 1;

    while (top > 0) {

	int last = stack[--top];
	int first = stack[--top];

	double x1 = Points->x[first];
	double y1 = Points->y[first];
	double z1 = Points->z[first];

	double x2 = Points->x[last];
	double y2 = Points->y[last];
	double z2 = Points->z[last];

	int maxindex = -1;
	double maxdist = -1;
	int i;

	for (i = first + 1; i <= last - 1; i++) {
	    double px, py, pz, pdist;
	    int status;
	    double dist =
		dig_distance2_point_to_line(Points->x[i], Points->y[i],
					    Points->z[i],
					    x1, y1, z1, x2, y2, z2, with_z,
					    &px, &py, &pz, &pdist, &status);

	    if (maxindex == -1 || dist > maxdist) {
		maxindex = i;
		maxdist = dist;
	    }
	}


	if (maxindex == -1 || maxdist <= thresh) {
	    index[icount++] = last;
	}
	else {

	    stack[top++] = maxindex;
	    stack[top++] = last;
	    stack[top++] = first;
	    stack[top++] = maxindex;
	}


    }


    Points->n_points = icount;


    for (i = 0; i < icount; i++) {
	Points->x[i] = Points->x[index[i]];
	Points->y[i] = Points->y[index[i]];
	Points->z[i] = Points->z[index[i]];
    }

    G_free(stack);
    G_free(index);
    return (Points->n_points);
}

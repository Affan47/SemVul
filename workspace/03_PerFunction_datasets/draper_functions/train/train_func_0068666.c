distance2d_ptarray_ptarray(POINTARRAY *l1, POINTARRAY *l2)
{
	double 	result = 99999999999.9;
	char result_okay = 0;
	int t,u;
	POINT2D	start, end;
	POINT2D	start2, end2;

	LWDEBUGF(2, "distance2d_ptarray_ptarray called (points: %d-%d)",
			l1->npoints, l2->npoints);

	getPoint2d_p(l1, 0, &start);
	for (t=1; t<l1->npoints; t++)
	{
		getPoint2d_p(l1, t, &end);

		getPoint2d_p(l2, 0, &start2);
		for (u=1; u<l2->npoints; u++)
		{
			double dist;

			getPoint2d_p(l2, u, &end2);

			dist = distance2d_seg_seg(&start, &end, &start2, &end2);

			LWDEBUGF(4, "line_line; seg %i * seg %i, dist = %g\n",t,u,dist);

			if (result_okay)
				result = LW_MIN(result,dist);
			else
			{
				result_okay = 1;
				result = dist;
			}

			LWDEBUGF(3, " seg%d-seg%d dist: %f, mindist: %f",
				t, u, dist, result);

			if (result <= 0) return 0;

			start2 = end2;
		}
		start = end;
	}

	return result;
}

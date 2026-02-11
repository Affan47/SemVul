lwgeom_polygon_area(LWPOLY *poly)
{
	double poly_area=0.0;
	int i;
	POINT2D p1;
	POINT2D p2;

	LWDEBUGF(2, "in lwgeom_polygon_area (%d rings)", poly->nrings);

	for (i=0; i<poly->nrings; i++)
	{
		int j;
		POINTARRAY *ring = poly->rings[i];
		double ringarea = 0.0;

		LWDEBUGF(4, " rings %d has %d points", i, ring->npoints);

		for (j=0; j<ring->npoints-1; j++)
    		{
			getPoint2d_p(ring, j, &p1);
			getPoint2d_p(ring, j+1, &p2);
			ringarea += ( p1.x * p2.y ) - ( p1.y * p2.x );
		}

		ringarea  /= 2.0;

		LWDEBUGF(4, " ring 1 has area %lf",ringarea);

		ringarea  = fabs(ringarea);
		if (i != 0)
			ringarea  = -1.0*ringarea ;

		poly_area += ringarea;
	}

	return poly_area;
}

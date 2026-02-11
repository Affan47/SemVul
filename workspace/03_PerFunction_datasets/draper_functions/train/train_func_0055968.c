line2d_rend(prim2d *ss, color2d rv, double x, double y) {
	line2d *s = (line2d *)ss;
	double rr, px, py;
	int j;

	px = x - s->lx0;
	py = y - s->ly0;


	if (s->t) {

		rr = (px * px) + (py * py) ;

		if (s->cap != 1)
			return 0;
		if (rr > s->ww)
			return 0;

	} else {

		double t, nx, ny;


		t = (s->vx * px + s->vy * py)/(s->vx * s->vx + s->vy * s->vy);

		if (t < 0.0) {
			if (s->cap != 1)
				return 0;
			rr = (px * px) + (py * py) ;
			if (rr > s->ww)
				return 0;

		} else if (t > 1.0) {
			if (s->cap != 1)
				return 0;
			rr = (x - s->lx1) * (x - s->lx1)
			   + (y - s->ly1) * (y - s->ly1);
			if (rr > s->ww)
				return 0;

		} else {
			double nx, ny;

			nx = t * s->vx;
			ny = t * s->vy;

			rr = (px - nx) * (px - nx) + (py - ny) * (py - ny);
			if (rr > s->ww)
				return 0;
		}
	}

	for (j = 0; j < s->ncc; j++)
		rv[j] = s->c[j];
	rv[PRIX2D] = s->ix;

	return 1;
}

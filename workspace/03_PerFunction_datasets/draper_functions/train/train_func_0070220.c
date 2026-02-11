point_add(struct point *r, struct point *p, struct point *q)
{
	u8 s[20], t[20], u[20];
	u8 *px, *py, *qx, *qy, *rx, *ry;
	struct point pp, qq;

	pp = *p;
	qq = *q;

	px = pp.x;
	py = pp.y;
	qx = qq.x;
	qy = qq.y;
	rx = r->x;
	ry = r->y;

	if (point_is_zero(&pp)) {
	elt_copy(rx, qx);
	elt_copy(ry, qy);
	return;
	}

	if (point_is_zero(&qq)) {
	elt_copy(rx, px);
	elt_copy(ry, py);
	return;
	}

	elt_sub(u, qx, px);

	if (elt_is_zero(u)) {
	elt_sub(u, qy, py);
	if (elt_is_zero(u))
	  point_double(r, &pp);
	else
	  point_zero(r);

	return;
	}

	elt_inv(t, u);
	elt_sub(u, qy, py);
	elt_mul(s, t, u);

	elt_square(rx, s);
	elt_add(t, px, qx);
	elt_sub(rx, rx, t);

	elt_sub(t, px, rx);
	elt_mul(ry, s, t);
	elt_sub(ry, ry, py);
}

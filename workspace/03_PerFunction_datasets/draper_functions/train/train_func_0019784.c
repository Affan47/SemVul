point_double(struct point *r, struct point *p)
{
	u8 s[20], t[20];
	struct point pp;
	u8 *px, *py, *rx, *ry;

	pp = *p;

	px = pp.x;
	py = pp.y;
	rx = r->x;
	ry = r->y;

	if (elt_is_zero(py)) {
	point_zero(r);
	return;
	}

	elt_square(t, px);
	elt_add(s, t, t);
	elt_add(s, s, t);
	elt_add(s, s, ec_a);
	elt_add(t, py, py);
	elt_inv(t, t);
	elt_mul(s, s, t);

	elt_square(rx, s);
	elt_add(t, px, px);
	elt_sub(rx, rx, t);

	elt_sub(t, px, rx);
	elt_mul(ry, s, t);
	elt_sub(ry, ry, py);
}

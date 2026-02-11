draw_arrow(GdkGC *gc, int fill,
    struct coord from, struct coord to, int len, double angle)
{
	struct coord p[3];
	struct coord side;

	if (from.x == to.x && from.y == to.y) {
		side.x = 0;
		side.y = -len;
	} else {
		side = normalize(sub_vec(to, from), len);
	}
	p[0] = add_vec(to, rotate(side, 180-angle));
	p[1] = to;
	p[2] = add_vec(to, rotate(side, 180+angle));
	draw_poly(gc, fill, p, 3);
}

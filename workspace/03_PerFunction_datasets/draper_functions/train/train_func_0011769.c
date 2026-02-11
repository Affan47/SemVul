tiff_hexagon(trend *ss,
	double x, double y,
	double w, double h,
	int step,
	char *id
) {
	tiff_trend *s = (tiff_trend *)ss;
	double vv[3][2];
	color2d cc[3];
	int i, j;

	if ((step & 1) == 0)
		x -= 0.25 * w;
	else
		x += 0.25 * w;
	y = y - 5.0/6.0 * h;
	h *= 2.0/3.0;


	for (i = 0; i < 3; i++)
		for (j = 0; j < s->r->ncc; j++)
			cc[i][j] = s->c[j];


	vv[0][0] = x;
	vv[0][1] = y + h;
	vv[1][0] = x + w;
	vv[1][1] = y + h;
	vv[2][0] = x + 0.5 * w;
	vv[2][1] = y + 1.5 * h;
	s->r->add(s->r, new_trivs2d(s->r, vv, cc));


	s->r->add(s->r, new_rect2d(s->r, x, y, w, h, s->c));


	vv[0][0] = x;
	vv[0][1] = y;
	vv[1][0] = x + w;
	vv[1][1] = y;
	vv[2][0] = x + 0.5 * w;
	vv[2][1] = y - 0.5 * h;
	s->r->add(s->r, new_trivs2d(s->r, vv, cc));
}

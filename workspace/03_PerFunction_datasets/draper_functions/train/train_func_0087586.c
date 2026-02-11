find_cc(struct gui_star *a, struct gui_star *b,
			  struct gui_star *ca, struct gui_star *cb,
			  struct gui_star *c, GSList *cat)
{
	double d_ccca;
	double pa_ccca;
	double xmin, xmax, ymin, ymax;
	double x, y;
	struct gui_star *cc;


	d_ccca = gui_star_distance(a, c) * gui_star_distance(ca, cb) / gui_star_distance(a, b);
	pa_ccca = (gui_star_pa(c, a) - gui_star_pa(b, a)) + gui_star_pa(cb, ca);

	x = ca->x + d_ccca * cos(pa_ccca);
	y = ca->y + d_ccca * sin(pa_ccca);


	xmin = x - MATCH_TOL;
	xmax = x + MATCH_TOL;
	ymin = y - MATCH_TOL;
	ymax = y + MATCH_TOL;

	while (cat != NULL) {
		cc = GUI_STAR(cat->data);
		cat = g_slist_next(cat);

		if (cc->x > xmax || cc->x < xmin || cc->y < ymin || cc->y > ymax)
			continue;
		return cc;
	}
	return NULL;
}

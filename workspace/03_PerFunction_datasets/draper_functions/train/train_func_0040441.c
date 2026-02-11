Polygon(Point *p, int n, int c, bool closed)
{
	int i;
	int lx, ly;
	if (!n) {
		return;
	}
	lx = p->x;
	ly = p->y;
	if(closed)
		Line(lx, ly, p[n-1].x, p[n-1].y, c);
	for (i=1; (i < n); i++) {
		p++;
		Line(lx, ly, p->x, p->y, c);
		lx = p->x;
		ly = p->y;
	}
}

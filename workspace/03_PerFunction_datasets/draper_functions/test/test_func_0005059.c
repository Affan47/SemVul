gdImageArc(gdImagePtr im, int cx, int cy, int w, int h, int s, int e, int color)
{
	int i;
	int lx = 0, ly = 0;
	int w2, h2;
	w2 = w/2;
	h2 = h/2;
	while (e < s) {
		e += 360;
	}
	for (i=s; (i <= e); i++) {
		int x, y;
		x = ((long)cost[i % 360] * (long)w2 / costScale) + cx;
		y = ((long)sint[i % 360] * (long)h2 / sintScale) + cy;
		if (i != s) {
			gdImageLine(im, lx, ly, x, y, color);
		}
		lx = x;
		ly = y;
	}
}

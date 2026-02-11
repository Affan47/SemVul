get_clipping(GB_DRAW *d, int *x, int *y, int *w, int *h)
{
	QRect r = DP(d)->clipRegion().boundingRect();

	if (x) *x = r.x();
	if (y) *y = r.y();
	if (w) *w = r.width();
	if (h) *h = r.height();
}

diff_rects_guts (Rect ra, Rect rb, int *count, Rect result[4])
{
	if (ra.x0 < rb.x0) {
		result[(*count)++] = make_rect (ra.x0, ra.y0, rb.x0, ra.y1);
	}
	if (ra.y0 < rb.y0) {
		result[(*count)++] = make_rect (ra.x0, ra.y0, ra.x1, rb.y0);
	}
	if (ra.x1 < rb.x1) {
		result[(*count)++] = make_rect (ra.x1, rb.y0, rb.x1, rb.y1);
	}
	if (ra.y1 < rb.y1) {
		result[(*count)++] = make_rect (rb.x0, ra.y1, rb.x1, rb.y1);
	}
}

_approx_in_rectangle(gdouble x, gdouble y, GdkRectangle *rect)
{
	const int off = 5;
	if (rect->width == 0 || rect->height == 0) {
		return FALSE;
	}
	else if (x >= rect->x-off && x < rect->x + rect->width + off &&
	    y >= rect->y-off && y < rect->y + rect->height + off) {
		return TRUE;
	}
	return FALSE;
}

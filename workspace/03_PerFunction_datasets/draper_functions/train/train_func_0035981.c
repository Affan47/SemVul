fvwmrect_do_intervals_intersect(
	int x1, int width1, int x2, int width2)
{
	return !(x1 + width1 <= x2 || x2 + width2 <= x1);
}

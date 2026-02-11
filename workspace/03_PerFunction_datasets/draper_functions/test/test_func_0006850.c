draw_line(GB_DRAW *d, int x1, int y1, int x2, int y2)
{
	DP(d)->drawLine(x1, y1, x2, y2);
	if (DPM(d)) DPM(d)->drawLine(x1, y1, x2, y2);
}

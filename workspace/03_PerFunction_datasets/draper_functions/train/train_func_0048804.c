drawSingleLine(int x1, int y1, int x2, int y2, uint16 pattern,
                               uint32 fgColor, uint32 bgColor, int logOp, bool last_pixel,
                               int cliprect[], int minmax[])
{
	if (clipLine(x1, y1, x2, y2, cliprect)) {
		D(bug("fVDI: %s %d,%d:%d,%d (%lx,%lx)", "drawSingleLine", x1, y1, x2, y2, fgColor, bgColor));
		hsDrawLine(x1, y1, x2, y2, pattern, fgColor, bgColor, logOp, last_pixel);
		if (x1 < x2) {
			if (x1 < minmax[0])
				minmax[0] = x1;
			if (x2 > minmax[2])
				minmax[2] = x2;
		} else {
			if (x2 < minmax[0])
				minmax[0] = x2;
			if (x1 > minmax[2])
				minmax[2] = x1;
		}
		if (y1 < y2) {
			if (y1 < minmax[1])
				minmax[1] = y1;
			if (y2 > minmax[3])
				minmax[3] = y2;
		} else {
			if (y2 < minmax[1])
				minmax[1] = y2;
			if (y1 > minmax[3])
				minmax[3] = y1;
		}
	}
	return 1;
}

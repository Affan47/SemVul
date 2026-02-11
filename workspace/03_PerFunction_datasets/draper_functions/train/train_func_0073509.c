connected_point_line(
	int x,
	int y,
	int x0,
	int y0,
	int x1,
	int y1
)
{
	if (x == x0 && y == y0) {
		return 1;
	} else if (x == x1 && y == y1) {
		return 1;
	} else if (x0 == x1) {
		if (x == x0
		 && MIN(y0, y1) <= y && y <= MAX(y0, y1)) {
			return 1;
		} else {
			return 0;
		}
	} else if (y0 == y1) {
		if (y == y0
		 && MIN(x0, x1) <= x && x <= MAX(x0, x1)) {
			return 1;
		} else {
			return 0;
		}
	} else {
#if DEBUG
		static int count = 0;

		if (count < 10) {
			fprintf(stderr, "WARNING: x0=%d, y0=%d, x1=%d, y1=%d\n",
					x0, y0, x1, y1);
			count++;
		} else if (count == 10) {
			fprintf(stderr, "WARNING: more warnings following...\n");
			count++;
		}
#endif

		return 0;
	}
}

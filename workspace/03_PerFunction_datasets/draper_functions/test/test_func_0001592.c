GetColumn(double *Image, long Width, long x, double *Line, long Height) {
	long y;

	Image = Image + x;
	for(y = 0L; y < Height; y++) {
		Line[y] = (double)*Image;
		Image += Width;
	}
}

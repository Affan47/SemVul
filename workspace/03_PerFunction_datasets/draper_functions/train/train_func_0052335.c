PutColumn(double *Image, long Width, long x, double *Line, long Height) {
	long	y;

	Image = Image + x;
	for(y = 0L; y < Height; y++) {
		*Image = (double)Line[y];
		Image += Width;
	}
}

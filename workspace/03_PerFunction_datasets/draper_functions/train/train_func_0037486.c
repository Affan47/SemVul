healpix_xy_to_nested(int hp, int Nside) {
	int bighp,x,y;
	int index;
	int i;

	healpix_decompose_xy(hp, &bighp, &x, &y, Nside);
	if (!is_power_of_two(Nside)) {
		fprintf(stderr, "healpix_xy_to_nested: Nside must be a power of two.\n");
		return -1;
	}


	index = 0;
	for (i=0; i<(8*sizeof(int)/2); i++) {
		index |= (((y & 1) << 1) | (x & 1)) << (i*2);
		y >>= 1;
		x >>= 1;
		if (!x && !y) break;
	}

	return index + bighp * Nside * Nside;
}

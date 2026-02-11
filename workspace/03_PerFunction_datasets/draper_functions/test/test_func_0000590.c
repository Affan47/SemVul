plot_grid_find_dec_label_location(plot_args_t* pargs, double dec, double cra, double ramin, double ramax, int dirn, double* pra) {
	double out;
	double in = cra;
	int i, N;
	anbool gotit;
	int dirs[2];
	int j, Ndir=0;
	logverb("Labelling Dec=%g\n", dec);
	gotit = FALSE;
	if (setdir(dirn, dirs, &Ndir))
		return -1;


	for (j=0; j<Ndir; j++) {
		int dir = dirs[j];
		for (i=1;; i++) {

			out = cra + i*dir*10.0;
			if (out > 370.0 || out <= -10)
				break;
			out = MIN(360, MAX(0, out));
			logverb("ra in=%g, out=%g\n", in, out);
			if (!plotstuff_radec_is_inside_image(pargs, out, dec)) {
				gotit = TRUE;
				break;
			}
			if (!isfinite(in) || !isfinite(out))
				break;
		}
		if (gotit)
			break;
	}
	if (!gotit) {
		ERROR("Couldn't find an RA outside the image for Dec=%g\n", dec);
		return -1;
	}
	i=0;
	N = 10;
	while (!plotstuff_radec_is_inside_image(pargs, in, dec)) {
		if (i == N)
			break;
		in = ramin + (double)i/(double)(N-1) * (ramax-ramin);
		i++;
	}
	if (!plotstuff_radec_is_inside_image(pargs, in, dec))
		return -1;
	while (fabs(out - in) > 1e-6) {

		double half;
		anbool isin;
		half = (out + in) / 2.0;
		isin = plotstuff_radec_is_inside_image(pargs, half, dec);
		if (isin)
			in = half;
		else
			out = half;
	}
	*pra = in;
	return 0;
}

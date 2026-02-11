phi1_(double qs, double Te, double Tone_es) {
	int i;
	double Phi, sinpi, cospi, con, com, dphi;

	Phi = asin (.5 * qs);
	if (Te < EPSILON)
		return( Phi );
	i = N_ITER;
	do {
		sinpi = sin (Phi);
		cospi = cos (Phi);
		con = Te * sinpi;
		com = 1. - con * con;
		dphi = .5 * com * com / cospi * (qs / Tone_es -
		   sinpi / com + .5 / Te * log ((1. - con) /
		   (1. + con)));
		Phi += dphi;
	} while (fabs(dphi) > TOL && --i);
	return( i ? Phi : HUGE_VAL );
}

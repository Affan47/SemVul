aacos(double v) {
	double av;

	if ((av = fabs(v)) >= 1.) {
		if (av > ONE_TOL)
			pj_errno = -19;
		return (v < 0. ? PI : 0.);
	}
	return acos(v);
}

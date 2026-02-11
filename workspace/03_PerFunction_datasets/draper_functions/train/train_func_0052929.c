computed_rake1(struct nodal_plane NP1)


{
	double rake2, sinrake2;
	double str2 = computed_strike1(NP1);
	double dip2 = computed_dip1(NP1);
	double am = (GMT_IS_ZERO (NP1.rake) ? 1. : NP1.rake / fabs(NP1.rake));
	double sd, cd, ss, cs;
	sincosd (NP1.dip, &sd, &cd);
	sincosd (NP1.str - str2, &ss, &cs);

	if (fabs(dip2 - 90.) < EPSIL)
		sinrake2 = am * cd;
	else
		sinrake2 = -am * sd * cs / cd;

	rake2 = d_atan2d(sinrake2, -am * sd * ss);

	return(rake2);
}

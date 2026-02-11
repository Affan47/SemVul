proj_radius(double str1,double dip1,double str)


{
	double dip, r;

	if (fabs(dip1 - 90.) < EPSIL) {


		r = (fabs(str - str1) < EPSIL || fabs(str - str1 - 180) < EPSIL) ? 1. : 0.;
	}
	else {
		dip = atan(tand(dip1) * sind(str - str1));
		r = sqrt(2.) * sin(M_PI_4 - dip / 2.);
	}
	return(r);
}

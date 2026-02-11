ps_plan(double x0,double y0,st_me meca,double size,GMT_LONG num_of_plane)


{

	GMT_LONG i;
	GMT_LONG npoints, lineout=1;

	double x[1000], y[1000];
	double radius_size;
	double str, radius, increment;
	double si, co;

	int rgb[3];

	rgb[0] = -1;
	rgb[1] = -1;
	rgb[2] = -1;


	radius_size = size * 0.5;


	ps_circle(x0, y0, radius_size*2., rgb, lineout);

	switch (num_of_plane) {
		case 1:
			i = -1;
			increment = 1.;
			str = meca.NP1.str;
			while (str <= meca.NP1.str + 180. + EPSIL) {
				i++;
				radius = proj_radius(meca.NP1.str, meca.NP1.dip, str) * radius_size;
				sincosd (str, &si, &co);
				x[i] = x0 + radius * si;
				y[i] = y0 + radius * co;
				str += increment;
			}
			npoints = i + 1;
			ps_line(x, y, npoints, 3, FALSE);
			break;

		case 2:
			i = -1;
			increment = 1.;
			str = meca.NP2.str;
			while (str <= meca.NP2.str + 180. + EPSIL) {
				i++;
				radius = proj_radius(meca.NP2.str, meca.NP2.dip, str) * radius_size;
				sincosd (str, &si, &co);
				x[i] = x0 + radius * si;
				y[i] = y0 + radius * co;
				str += increment;
			}
			npoints = i + 1;
			ps_line(x, y, npoints, 3, FALSE);
			break;
	}
	return(radius_size*2.);
}

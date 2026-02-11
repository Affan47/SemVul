GMT_quickconic (void)
{


	double s, dlon, width;

	if (project_info.gave_map_width) {
		dlon = project_info.e - project_info.w;
		width = project_info.pars[4] * GMT_u2u[gmtdefs.measure_unit][GMT_M];
		s = (dlon * project_info.M_PR_DEG) / width;
	}
	else if (project_info.units_pr_degree) {

		s = project_info.M_PR_DEG / (project_info.pars[4] * GMT_u2u[gmtdefs.measure_unit][GMT_M]);
	}
	else {
		s = (1.0 / project_info.pars[4]) / project_info.unit;
	}

	if (s > 1.0e7) {
		if (gmtdefs.verbose) fprintf (stderr, "GMT Warning: Using spherical projection with conformal latitudes\n");
		return (TRUE);
	}
	else
		return (FALSE);
}

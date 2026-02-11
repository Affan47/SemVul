GMT_map_init_polar (void)
{
	double xmin, xmax, ymin, ymax;

	GMT_vpolar (project_info.pars[1]);
	if (project_info.got_elevations) {
		if (project_info.s < 0.0 || project_info.n > 90.0) {
			fprintf (stderr, "%s: ERROR: -JP...r for elevation plots requires s >= 0 and n <= 90!\n", GMT_program);
			GMT_exit (EXIT_FAILURE);
		}
		if (GMT_IS_ZERO (90.0 - project_info.n)) project_info.edge[2] = FALSE;
	}
	else {
		if (GMT_IS_ZERO (project_info.s)) project_info.edge[0] = FALSE;
	}
	if (GMT_360_RANGE (project_info.w, project_info.e)) project_info.edge[1] = project_info.edge[3] = FALSE;
	GMT_left_edge = (PFD) GMT_left_circle;
	GMT_right_edge = (PFD) GMT_right_circle;
	GMT_forward = (PFL) GMT_polar;
	GMT_inverse = (PFL) GMT_ipolar;
	GMT_world_map = FALSE;
	GMT_xy_search (&xmin, &xmax, &ymin, &ymax, project_info.w, project_info.e, project_info.s, project_info.n);
	project_info.x_scale = project_info.y_scale = project_info.pars[0];
	GMT_map_setinfo (xmin, xmax, ymin, ymax, project_info.pars[0]);
	GMT_geo_to_xy (project_info.central_meridian, project_info.pole, &project_info.c_x0, &project_info.c_y0);


	project_info.r = project_info.y_scale * project_info.n;
	GMT_outside = (PFL) GMT_polar_outside;
	GMT_crossing = (PFL) GMT_wesn_crossing;
	GMT_overlap = (PFL) GMT_wesn_overlap;
	GMT_map_clip = (PFL) GMT_wesn_clip;
	frame_info.horizontal = TRUE;
	if (!project_info.got_elevations) gmtdefs.degree_format = -1;
	GMT_n_lat_nodes = 2;
	GMT_meridian_straight = TRUE;

	return (FALSE);
}

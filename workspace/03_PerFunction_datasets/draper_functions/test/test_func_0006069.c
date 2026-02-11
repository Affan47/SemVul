GMT_map_init_cassini (void) {
	GMT_LONG too_big;
	double xmin, xmax, ymin, ymax;

	if (GMT_is_dnan(project_info.pars[0])) project_info.pars[0] = 0.5 * (project_info.w + project_info.e);
	too_big = GMT_quicktm (project_info.pars[0], 4.0);
	if (too_big) GMT_set_spherical();
	GMT_vcassini (project_info.pars[0], project_info.pars[1]);
	if (GMT_IS_SPHERICAL) {
		GMT_forward = (PFL) GMT_cassini_sph;
		GMT_inverse = (PFL) GMT_icassini_sph;
	}
	else {
		GMT_forward = (PFL) GMT_cassini;
		GMT_inverse = (PFL) GMT_icassini;
	}
	if (project_info.units_pr_degree) project_info.pars[2] /= project_info.M_PR_DEG;
	project_info.x_scale = project_info.y_scale = project_info.pars[2];
	if (gmtdefs.basemap_type == GMT_IS_FANCY) gmtdefs.basemap_type = GMT_IS_PLAIN;

	if (project_info.region) {
		GMT_xy_search (&xmin, &xmax, &ymin, &ymax, project_info.w, project_info.e, project_info.s, project_info.n);
		GMT_outside = (PFL) GMT_wesn_outside;
		GMT_crossing = (PFL) GMT_wesn_crossing;
		GMT_overlap = (PFL) GMT_wesn_overlap;
		GMT_map_clip = (PFL) GMT_wesn_clip;
		GMT_left_edge = (PFD) GMT_left_conic;
		GMT_right_edge = (PFD) GMT_right_conic;
	}
	else {
		(*GMT_forward) (project_info.w, project_info.s, &xmin, &ymin);
		(*GMT_forward) (project_info.e, project_info.n, &xmax, &ymax);
		GMT_outside = (PFL) GMT_rect_outside;
		GMT_crossing = (PFL) GMT_rect_crossing;
		GMT_overlap = (PFL) GMT_rect_overlap;
		GMT_map_clip = (PFL) GMT_rect_clip;
		GMT_left_edge = (PFD) GMT_left_rect;
		GMT_right_edge = (PFD) GMT_right_rect;
		frame_info.check_side = TRUE;
	}

	frame_info.horizontal = TRUE;
	GMT_map_setinfo (xmin, xmax, ymin, ymax, project_info.pars[2]);

	return (!project_info.region);
}

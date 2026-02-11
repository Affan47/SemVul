spotter_finite_to_stages (struct EULER p[], GMT_LONG n, GMT_LONG finite_rates, GMT_LONG stage_rates)
{


	GMT_LONG i;
	double *elon = NULL, *elat = NULL, *ew = NULL, t_old;
	double R_young[3][3], R_old[3][3], R_stage[3][3];


	elon = (double *) GMT_memory (VNULL, (size_t)n, sizeof (double), "libspotter");
	elat = (double *) GMT_memory (VNULL, (size_t)n, sizeof (double), "libspotter");
	ew   = (double *) GMT_memory (VNULL, (size_t)n, sizeof (double), "libspotter");

	set_I_matrix (R_young);

	t_old = 0.0;
	for (i = 0; i < n; i++) {
		if (finite_rates) p[i].omega *= p[i].duration;
		spotter_make_rot_matrix (p[i].lon, p[i].lat, p[i].omega, R_old);
		spotter_matrix_mult (R_young, R_old, R_stage);
		matrix_to_pole (R_stage, &elon[i], &elat[i], &ew[i]);
		if (elon[i] > 180.0) elon[i] -= 360.0;
		spotter_matrix_transpose (R_young, R_old);
		p[i].t_stop = t_old;
		t_old = p[i].t_start;
	}


	xyw_to_struct_euler (p, elon, elat, ew, n, TRUE, stage_rates);

	GMT_free ((void *)elon);
	GMT_free ((void *)elat);
	GMT_free ((void *)ew);

	reverse_rotation_order (p, n);
}

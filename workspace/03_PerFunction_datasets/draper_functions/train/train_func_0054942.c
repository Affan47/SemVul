spotter_stages_to_finite (struct EULER p[], GMT_LONG n, GMT_LONG finite_rates, GMT_LONG stage_rates)
{


	GMT_LONG i;
	double *elon = NULL, *elat = NULL, *ew = NULL;
	double R_young[3][3], R_old[3][3], R_stage[3][3];


	reverse_rotation_order (p, n);

	elon = (double *) GMT_memory (VNULL, (size_t)n, sizeof (double), "libspotter");
	elat = (double *) GMT_memory (VNULL, (size_t)n, sizeof (double), "libspotter");
	ew   = (double *) GMT_memory (VNULL, (size_t)n, sizeof (double), "libspotter");

	set_I_matrix (R_old);

	for (i = 0; i < n; i++) {
		if (stage_rates) p[i].omega *= p[i].duration;
		spotter_make_rot_matrix (p[i].lon, p[i].lat, p[i].omega, R_stage);
		spotter_matrix_mult (R_old, R_stage, R_young);
		memcpy ((void *)R_old, (void *)R_young, (size_t)(9 * sizeof (double)));
		matrix_to_pole (R_young, &elon[i], &elat[i], &ew[i]);
		if (elon[i] > 180.0) elon[i] -= 360.0;
	}


	xyw_to_struct_euler (p, elon, elat, ew, n, FALSE, finite_rates);

	GMT_free ((void *)elon);
	GMT_free ((void *)elat);
	GMT_free ((void *)ew);
}

write_output (struct SURFACE_INFO *C, char *grdfile)
{
	GMT_LONG	index, i, j, k;
	float *u, *v2;
	u = C->u;

	load_constraints (C, FALSE);

	strcpy (C->h.title, GMT_program);

	v2 = (float *) GMT_memory (VNULL, (size_t)C->nxny, sizeof (float), GMT_program);
	index = C->ij_sw_corner;
	for (i = 0; i < C->nx; i++, index += C->my) {
		for (j = 0; j < C->ny; j++) {
			k = j * C->nx + i;
			v2[k] = u[index + C->ny - j - 1];
			if (C->set_low  && !GMT_is_fnan (C->lower[k]) && v2[k] < C->lower[k]) v2[k] = C->lower[k];
			if (C->set_high && !GMT_is_fnan (C->upper[k]) && v2[k] > C->upper[k]) v2[k] = C->upper[k];
		}
	}

	GMT_err_fail (GMT_write_grd (grdfile, &(C->h), v2, 0.0, 0.0, 0.0, 0.0, GMT_pad, FALSE), grdfile);
	GMT_free ((void *)v2);
	if (C->set_low) GMT_free ((void *)C->lower);
	if (C->set_high) GMT_free ((void *)C->upper);
}

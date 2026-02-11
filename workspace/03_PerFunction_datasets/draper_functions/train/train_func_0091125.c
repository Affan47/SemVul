polish_iter (GnmNlsolve *nl)
{
	GnmSolver *sol = nl->parent;
	const int n = nl->vars->len;
	gnm_float *x;
	gnm_float step;
	gboolean any_at_all = FALSE;

	x = g_new (gnm_float, n);
	for (step = gnm_pow2 (-10); step > GNM_EPSILON; step *= 0.75) {
		int c, s;

		for (c = 0; c < n; c++) {
			for (s = 0; s <= 1; s++) {
				gnm_float y;
				gnm_float dx = step * gnm_abs (nl->xk[c]);

				if (dx == 0) dx = step;
				if (s) dx = -dx;

				memcpy (x, nl->xk, n * sizeof (gnm_float));
				x[c] += dx;
				set_vector (nl, x);
				y = get_value (nl);

				if (y < nl->yk && gnm_solver_check_constraints (sol))  {
					nl->yk = y;
					memcpy (nl->xk, x, n * sizeof (gnm_float));
					any_at_all = TRUE;
					if (nl->debug)
						g_printerr ("Polish step %.15" GNM_FORMAT_g
							    " in direction %d\n",
							    dx, c);
					break;
				}
			}
		}
	}

	g_free (x);

	if (any_at_all)
		gnm_nlsolve_set_solution (nl);

	return any_at_all;
}

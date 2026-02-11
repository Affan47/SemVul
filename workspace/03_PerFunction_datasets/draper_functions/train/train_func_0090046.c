solve_system (double *gtg, double *gtd, double *model, GMT_LONG n_model, GMT_LONG mp, double *lambda, double *v, double *b, double *z, double c_no, GMT_LONG *ir)
{

	GMT_LONG	i, j, k, rank = 0, nrots;
	GMT_LONG n, m;
	double	c_test, temp_inverse_ij;

	if (n_model == 1) {
		model[0] = gtd[0] / gtg[0];
		*ir = 1;
	}
	else {
		n = n_model;
		m = mp;
		if(GMT_jacobi(gtg, &n, &m, lambda, v, b, z, &nrots)) {
			fprintf(stderr,"trend2d:  Warning:  Matrix Solver Convergence Failure.\n");
		}
		c_test = fabs(lambda[0])/c_no;
		while(rank < n_model && lambda[rank] > 0.0 && lambda[rank] > c_test) rank++;
		for (i = 0; i < n_model; i++) {
			model[i] = 0.0;
			for (j = 0; j < n_model; j++) {
				temp_inverse_ij = 0.0;
				for (k = 0; k <  rank; k++) {
					temp_inverse_ij += (v[i + k*mp] * v[j + k*mp] / lambda[k]);
				}
				model[i] += (temp_inverse_ij * gtd[j]);
			}
		}
		*ir = rank;
	}
}

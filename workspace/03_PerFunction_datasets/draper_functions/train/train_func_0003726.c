solve(SylvParams& pars, KronVector& x) const
{
	int max_steps = *(pars.max_num_iter);
	int steps = 1;
	double max_norm = *(pars.convergence_tol);
	double norm = performFirstStep(x);

	QuasiTriangular* kpow = matrixK->clone();
	QuasiTriangular* fpow = matrixF->clone();
	while (steps < max_steps && norm > max_norm) {
		kpow->multRight(SqSylvMatrix(*kpow));
		fpow->multRight(SqSylvMatrix(*fpow));
		norm = performStep(*kpow, *fpow, x);
		steps++;
	}

	delete fpow;
	delete kpow;

	pars.converged = (norm <= max_norm);
	pars.iter_last_norm = norm;
	pars.num_iter = steps;
}

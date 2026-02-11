randvec_gaussian(double* v, MatrixDouble& mu, MatrixDouble& sigma) {
	if(_randvec_gaussian_tmp_d.width != mu.width)
		_randvec_gaussian_tmp_d.realloc(mu.width, 1);

	randvec_gaussian(_randvec_gaussian_tmp_d, mu.width);
	for(int i=0; i<mu.width; i++) v[i] = mu[i];
	matrix_CpAtB_double(v, sigma, _randvec_gaussian_tmp_d, sigma.width, sigma.width, 1);
}

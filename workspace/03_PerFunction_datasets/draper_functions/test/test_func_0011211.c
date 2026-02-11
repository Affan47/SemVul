multVec(Vector& x, const ConstVector& b) const
{
	x = b;
	blas_int nn = diagonal.getSize();
	blas_int lda = diagonal.getSize();
	blas_int incx = x.skip();
	dtrmv("U", "N", "N", &nn, getData().base(), &lda, x.base(), &incx);
	for (const_diag_iter di = diag_begin(); di != diag_end(); ++di) {
		if (!(*di).isReal()) {
			int jbar = (*di).getIndex();
			x[jbar+1] += (*di).getBeta2()*(b[jbar]);
		}
	}
}

gen_sylv_solve_and_check(int order, int n, int m, int zero_cols,
							  const double* A, const double* B,
							  const double* C, const double* D,
							  double* X, mxArray*& p)
{
		GeneralSylvester s(order, n, m, zero_cols, A, B, C, X, true);
		s.solve();
		s.check(D);
		p = s.getParams().createStructArray();
}

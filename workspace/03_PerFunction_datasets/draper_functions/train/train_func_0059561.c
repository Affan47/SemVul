solvii(double alpha, double beta1, double beta2,
								 KronVector& d1, KronVector& d2,
								 double& eig_min) const
{
	KronVector d1tmp(d1);
	KronVector d2tmp(d2);
	linEval(alpha, beta1, beta2, d1, d2, d1tmp, d2tmp);
	solviip(alpha, beta1*beta2, d1, eig_min);
	solviip(alpha, beta1*beta2, d2, eig_min);
}

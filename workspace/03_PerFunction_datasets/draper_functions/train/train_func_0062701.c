backsub(
	const double *b,
	double       *sol,
	const size_t N) const
{
	ASSERT_(N>0)
	std::vector<double> tmp(N);

	cs_ipvec(m_symbolic_structure->pinv,&b[0],&tmp[0],N);

	cs_lsolve(m_numeric_structure->L,&tmp[0]);
	cs_ltsolve(m_numeric_structure->L,&tmp[0]);
	cs_pvec(m_symbolic_structure->pinv,&tmp[0],&sol[0],N);


}

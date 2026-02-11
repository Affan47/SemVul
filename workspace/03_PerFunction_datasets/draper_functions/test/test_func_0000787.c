evaluatePDF(
	const	CPose2D &x,
	bool	sumOverAllPhis ) const
{
	if (!sumOverAllPhis)
	{

		CMatrixDouble31	X = CMatrixDouble31(x);
		CMatrixDouble31	MU;
		double	ret = 0;

		for (const_iterator it=m_modes.begin();it!=m_modes.end();++it)
		{
			MU = CMatrixDouble31((it)->mean);
			ret+= exp((it)->log_w) * math::normalPDF( X, MU, (it)->cov );
		}

		return ret;
	}
	else
	{

		CMatrixDouble	X(2,1), MU(2,1),COV(2,2);
		double	ret = 0;

		X(0,0) = x.x();
		X(1,0) = x.y();

		for (const_iterator it=m_modes.begin();it!=m_modes.end();++it)
		{
			MU(0,0) = (it)->mean.x();
			MU(1,0) = (it)->mean.y();

			COV(0,0) = (it)->cov(0,0);
			COV(1,1) = (it)->cov(1,1);
			COV(0,1) = COV(1,0) = (it)->cov(0,1);

			ret+= exp((it)->log_w) * math::normalPDF( X, MU, COV );
		}

		return ret;
	}
}

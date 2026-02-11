alpha2index( double alpha ) const
{
	mrpt::math::wrapToPi(alpha);
	int k = mrpt::utils::round(0.5*(m_alphaValuesCount*(1.0+alpha/M_PI) - 1.0));
	if (k<0) k=0;
	if (k>=m_alphaValuesCount) k=m_alphaValuesCount-1;
	return (uint16_t)k;
}

copyFrom(const CPose3DPDF &o)
{
	MRPT_START

	if (this == &o) return;

	if (o.GetRuntimeClass()==CLASS_ID(CPose3DPDFSOG))
	{
		*this = *static_cast<const CPose3DPDFSOG*>(&o);
	}
	else
	{
		this->resize(1);
		m_modes[0].log_w = 0;
		mrpt::math::CMatrixDouble66 C;
		o.getCovarianceAndMean( C, m_modes[0].val.mean );
		m_modes[0].val.cov = C;
	}

	MRPT_END
}

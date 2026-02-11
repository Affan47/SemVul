getMean(CPose2D &est_) const
{

	const size_t n = m_particles.size();
	if (n)
	{
		mrpt::poses::SE_average<2> se_averager;
		for (size_t i=0;i<n;i++)
		{
			const CPose2D &p  = *m_particles[i].d;
			double w  = exp(m_particles[i].log_w);
			se_averager.append(p,w);
		}
		se_averager.get_average(est_);
	}
	else
	{
		est_ = CPose2D();
	}
}

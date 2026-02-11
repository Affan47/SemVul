clear( const CPose3D &initialPose )
{
	size_t	i,M = m_particles.size();

	for (i=0;i<M;i++)
	{
		m_particles[i].log_w = 0;

		m_particles[i].d->mapTillNow.clear();

		m_particles[i].d->robotPath.resize(1);
		m_particles[i].d->robotPath[0]=initialPose;
	}

	SFs.clear();
	SF2robotPath.clear();

	averageMapIsUpdated = false;
}

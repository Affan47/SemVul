PF_SLAM_implementation_replaceByNewParticleSet(
	CParticleList	&old_particles,
	const vector<TPose3D>	&newParticles,
	const vector<double>	&newParticlesWeight,
	const vector<size_t>	&newParticlesDerivedFromIdx )  const
{
	MRPT_UNUSED_PARAM(newParticlesDerivedFromIdx);
	ASSERT_(size_t(newParticlesWeight.size())==newParticles.size())


	for (size_t i=0;i<old_particles.size();i++)
			mrpt::utils::delete_safe( old_particles[ i ].d );


	const size_t N = newParticles.size();
	old_particles.resize(N);
	for (size_t i=0;i<N;i++)
	{
		old_particles[i].log_w = newParticlesWeight[i];
		old_particles[i].d = new CPose3D( newParticles[i] );
	}
}

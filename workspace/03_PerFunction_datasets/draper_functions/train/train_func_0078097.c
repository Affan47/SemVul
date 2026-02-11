saveToTextFile(const std::string &file) const
{
	MRPT_START

	FILE	*f=os::fopen(file.c_str(),"wt");
	if (!f) return;

	size_t i,N = m_particles.size();
	for (i=0;i<N;i++)
		os::fprintf(f,"%f %f %f %e\n", m_particles[i].d->x,m_particles[i].d->y,m_particles[i].d->z,m_particles[i].log_w);

	os::fclose(f);

	MRPT_END
}

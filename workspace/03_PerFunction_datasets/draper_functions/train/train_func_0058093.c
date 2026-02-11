pGenParticleGroups(int p_group_count, int max_particles)
{
	_ParticleState &_ps = _GetPState();

	if(_ps.in_new_list)
		return -1;

	_PLock();


	int ind = _ps.GenerateGroups(p_group_count);

	for(int i=ind; i<ind+p_group_count; i++)
	{
		_ps.group_list[i] = (ParticleGroup *)new
			Particle[max_particles + 2];
		_ps.group_list[i]->max_particles = max_particles;
		_ps.group_list[i]->particles_allocated = max_particles;
		_ps.group_list[i]->p_count = 0;
	}

	_PUnLock();

	return ind;
}

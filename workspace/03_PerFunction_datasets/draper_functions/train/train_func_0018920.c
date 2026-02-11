particle_move_all(float frametime)
{
	MONITOR_INC( NumParticles, Num_particles );

	if ( !Particles_enabled )
		return;

	if ( Particles.empty() )
		return;

	for (SCP_vector<particle*>::iterator p = Particles.begin(); p != Particles.end(); )
	{
		particle* part = *p;
		if (part->age == 0.0f) {
			part->age = 0.00001f;
		} else {
			part->age += frametime;
		}

		bool remove_particle = false;


		if (part->age > part->max_life) {

			if ( (part->age > frametime) || (part->max_life > 0.0f) ) {
				remove_particle = true;
			}
		}


		if (part->attached_objnum >= 0) {

			if ( (part->attached_objnum >= MAX_OBJECTS) || (part->attached_sig != Objects[part->attached_objnum].signature) ) {
				remove_particle = true;
			}
		}

		if (remove_particle)
		{
			part->signature = 0;
			delete part;


			if (p + 1 == Particles.end())
			{
				Particles.pop_back();
				break;
			}
			else
			{
				*p = Particles.back();
				Particles.pop_back();
				continue;
			}
		}


		vm_vec_scale_add2( &part->pos, &part->velocity, frametime );


		++p;
	}
}

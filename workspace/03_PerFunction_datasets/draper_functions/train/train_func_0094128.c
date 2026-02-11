Execute(ParticleGroup *group)
{
	float magdt = magnitude * dt;
	float max_radiusSqr = max_radius * max_radius;

	if(max_radiusSqr < P_MAXFLOAT)
	{
		for(int i = 0; i < group->p_count; i++)
		{
			Particle &m = group->list[i];


			pVector dir(m.pos - center);


			float rSqr = dir.length2();

			if(rSqr < max_radiusSqr)
			{
				pVector accel;
				acc.Generate(accel);


				m.vel += accel * (magdt / (rSqr + epsilon));
			}
		}
	}
	else
	{
		for(int i = 0; i < group->p_count; i++)
		{
			Particle &m = group->list[i];


			pVector dir(m.pos - center);


			float rSqr = dir.length2();

			pVector accel;
			acc.Generate(accel);


			m.vel += accel * (magdt / (rSqr + epsilon));
		}
	}
}

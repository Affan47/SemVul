CL_SmokeTrail (vec3_t start, vec3_t end, int colorStart, int colorRun, int spacing)
{
	vec3_t		move;
	vec3_t		vec;
	float		len;
	int			j;
	particle_t	*p;

	VectorCopy (start, move);
	VectorSubtract (end, start, vec);
	len = VectorNormalize (vec);

	VectorScale (vec, spacing, vec);


	while (len > 0)
	{
		len -= spacing;

		if (!(p = new_particle()))
			return;
		VectorClear (p->accel);

		p->alpha = 1.0;
		p->alphavel = -1.0 / (1+frand()*0.5);
		p->color = colorStart + (rand() % colorRun);
		for (j=0 ; j<3 ; j++)
		{
			p->org[j] = move[j] + crand()*3;
			p->accel[j] = 0;
		}
		p->vel[2] = 20 + crand()*5;

		VectorAdd (move, vec, move);
	}
}

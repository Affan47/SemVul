CL_ItemRespawnParticles (vec3_t org)
{
	int			i, j;
	particle_t	*p;

	for (i=0 ; i<64 ; i++)
	{
		if (!(p = new_particle()))
			return;

		p->color = 0x74 + (rand()&7);
		p->scale = 12 + (rand()&7) ;
		p->scalevel = 0;
		p->type = PARTICLE_STANDARD;
		p->image = r_explosiontexture;
		p->blendsrc = GL_SRC_ALPHA;
		p->blenddst = GL_ONE;
		p->org[0] = org[0] + crand()*16;
		p->org[1] = org[1] + crand()*16;
		p->org[2] = org[2] + crand()*16;

		for (j=0 ; j<3 ; j++)
			p->vel[j] = crand()*8;

		p->accel[0] = p->accel[1] = 0;
		p->accel[2] = -PARTICLE_GRAVITY*0.2;
		p->alpha = .3;

		p->alphavel = -1.0 / (1.0 + frand()*0.3);

		if (i < 4)
			addParticleLight (p,
						p->scale*30, 10,
					0, 1, 1);

	}
}

CL_BlueTeamLight(vec3_t pos)
{

	int			i,j;
	particle_t	*p;

	if(!server_is_team && !cl_dmlights->value)
		return;

	for(i=1; i<3; i++) {
		if (!(p = new_particle()))
			return;

		VectorClear (p->accel);

		p->alpha = .7;
		p->type = PARTICLE_STANDARD;
		p->image = r_flaretexture;
		p->blendsrc = GL_ONE;
		p->blenddst = GL_ONE;
		if (server_is_team)
			p->color = 0x74;
		else
			p->color = 0xd3;
		p->scale = 10*i;
		p->alphavel = INSTANT_PARTICLE;
		for (j=0 ; j<3 ; j++)
		{
			p->org[j] = pos[j];
			p->vel[j] = 0;
			p->accel[j] = 0;
		}
	}
}

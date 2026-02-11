PM_CheckSpecialMovement (void)
{
	vec3_t	spot;
	int		cont;
	vec3_t	flatforward;
	trace_t	trace;

	if (pm->s.pm_time)
		return;

	pml.ladder = false;


	flatforward[0] = pml.forward[0];
	flatforward[1] = pml.forward[1];
	flatforward[2] = 0;
	VectorNormalize (flatforward);

	VectorMA (pml.origin, 1, flatforward, spot);
	trace = pm->trace (pml.origin, pm->mins, pm->maxs, spot);
	if ((trace.fraction < 1) && (trace.contents & CONTENTS_LADDER))
		pml.ladder = true;


	if (pm->waterlevel != 2)
		return;

	VectorMA (pml.origin, 30, flatforward, spot);
	spot[2] += 4;
	cont = pm->pointcontents (spot);
	if (!(cont & CONTENTS_SOLID))
		return;

	spot[2] += 16;
	cont = pm->pointcontents (spot);
	if (cont)
		return;

	VectorScale (flatforward, 50, pml.velocity);
	pml.velocity[2] = 350;

	pm->s.pm_flags |= PMF_TIME_WATERJUMP;
	pm->s.pm_time = 255;
}

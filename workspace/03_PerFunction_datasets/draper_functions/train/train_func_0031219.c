PM_DeadMove (void)
{
	float	forward;

	if (!pm->groundentity)
		return;


	forward = VectorLength (pml.velocity);
	forward -= 20;
	if (forward <= 0)
	{
		VectorClear (pml.velocity);
	}
	else
	{
		VectorNormalize (pml.velocity);
		VectorScale (pml.velocity, forward, pml.velocity);
	}
}

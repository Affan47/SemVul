PM_ClampAngles (void)
{
	int16	temp;
	int		i;

	if (pm->s.pm_flags & PMF_TIME_TELEPORT)
	{
		pm->viewangles[YAW] = SHORT2ANGLE(pm->cmd.angles[YAW] + pm->s.delta_angles[YAW]);
		pm->viewangles[PITCH] = pm->viewangles[ROLL] = 0;
	}
	else
	{

		for (i=0 ; i<3 ; i++) {
			temp = pm->cmd.angles[i] + pm->s.delta_angles[i];
			pm->viewangles[i] = SHORT2ANGLE(temp);
		}


		if (pm->viewangles[PITCH] > 89 && pm->viewangles[PITCH] < 180)
			pm->viewangles[PITCH] = 89;
		else if (pm->viewangles[PITCH] < 271 && pm->viewangles[PITCH] >= 180)
			pm->viewangles[PITCH] = 271;
	}
	AngleVectors (pm->viewangles, pml.forward, pml.right, pml.up);
}

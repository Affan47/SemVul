CL_KeyState (kbutton_t *key)
{
	float		val;
	int			msec;

	key->state &= 1;

	msec = key->msec;
	key->msec = 0;

	if (key->state)
	{
		msec += sys_frame_time - key->downtime;
		key->downtime = sys_frame_time;
	}

#if 0
	if (msec)
	{
		Com_Printf ("%i ", msec);
	}
#endif

	val = (float)msec / frame_msec;
	if (val < 0)
		val = 0;
	if (val > 1)
		val = 1;

	return val;
}

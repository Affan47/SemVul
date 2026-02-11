player_can_read(void)
{
	if (p_ptr->timed[TMD_BLIND])
	{
		msg("You can't see anything.");
		return FALSE;
	}

	if (no_light())
	{
		msg("You have no light to read by.");
		return FALSE;
	}

	if (p_ptr->timed[TMD_CONFUSED])
	{
		msg("You are too confused to read!");
		return FALSE;
	}

	if (p_ptr->timed[TMD_AMNESIA])
	{
		msg("You can't remember how to read!");
		return FALSE;
	}

	return TRUE;
}

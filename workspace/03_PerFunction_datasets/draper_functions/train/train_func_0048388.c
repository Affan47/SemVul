__is_restack_transients_needed(
	FvwmWindow *t, stack_mode_t mode)
{
	if (DO_RAISE_TRANSIENT(t))
	{
		if (mode == SM_RAISE || mode == SM_RESTACK)
		{
			return True;
		}
	}
	if (DO_LOWER_TRANSIENT(t))
	{
		if (mode == SM_LOWER || mode == SM_RESTACK)
		{
			return True;
		}
	}

	return False;
}

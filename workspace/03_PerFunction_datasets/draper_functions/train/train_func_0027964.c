property_change(FvwmPacketBody *body)
{
	WinManager *man = NULL;
	int j;

	if (body->property_data.id != 0)
	{
		if (!(man = find_windows_manager(body->property_data.id)))
			return;
	}

	if (body->property_data.arg == MX_PROPERTY_CHANGE_BACKGROUND)
	{
		if (man != NULL &&
		    CSET_IS_TRANSPARENT_PR(man->colorsets[DEFAULT]))
		{
			recreate_background(man, DEFAULT);
			force_manager_redraw(man);
		}
		if (man != NULL)
		{
			return;
		}
		for (j = 0; j < globals.num_managers; j++)
		{
			man = &globals.managers[j];
			if (CSET_IS_TRANSPARENT_PR(man->colorsets[DEFAULT]))
			{
				recreate_background(man, DEFAULT);
				force_manager_redraw(man);
			}
		}
	}
	else if (body->property_data.arg == MX_PROPERTY_CHANGE_SWALLOW &&
		man != NULL)
	{
		man->swallowed = body->property_data.toggle;
		if (man->swallowed && body->property_data.str)
		{
			unsigned long u;

			if (sscanf((char *)body->property_data.str, "%lu",
				   &u) == 1)
			{
				man->swallower_win = (Window)u;
			}
			else
			{
				man->swallower_win = 0;
			}
		}
	}
}

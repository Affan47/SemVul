borg_maintain_light(void)
{
	int i;
	borg_item *current_light = &borg_items[INVEN_LIGHT];


	if (current_light->tval == TV_LIGHT)
	{
		if (current_light->sval == SV_LIGHT_TORCH)
		{
			if (current_light->timeout > 250)
			{
				return BORG_NO_NEED;
			}
			else
			{

				i = borg_slot(TV_LIGHT, SV_LIGHT_TORCH);
				if (i < 0)
					return BORG_UNMET_NEED;


				return BORG_NO_NEED;
			}
		}


		if (current_light->sval == SV_LIGHT_LANTERN)
		{

			if (borg_items[INVEN_LIGHT].timeout < 1000)
			{
				if (borg_refuel_lantern())
					return BORG_MET_NEED;

				return BORG_UNMET_NEED;
			}
		}
		return BORG_NO_NEED;
	}
	else
	{
		i = borg_slot(TV_LIGHT, SV_LIGHT_LANTERN);
		if (i < 0)
		{
			i = borg_slot(TV_LIGHT, SV_LIGHT_TORCH);
		}

		if (i < 0)
		{
			return BORG_UNMET_NEED;
		} else {
			borg_keypress('w');
			borg_keypress(I2A(i));
			return BORG_MET_NEED;
		}
	}
}

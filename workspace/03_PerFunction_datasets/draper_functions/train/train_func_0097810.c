style_parse_icon_size_style(
	char *option, char *rest, window_style *ps)
{
	int vals[4];
	int i;

	option = PeekToken(rest, NULL);
	if (StrEquals(option, "Stretched"))
	{
		SSET_ICON_RESIZE_TYPE(*ps, ICON_RESIZE_TYPE_STRETCHED);
		option = PeekToken(rest, &rest);
	}
	else if (StrEquals(option, "Adjusted"))
	{
		SSET_ICON_RESIZE_TYPE(*ps, ICON_RESIZE_TYPE_ADJUSTED);
		option = PeekToken(rest, &rest);
	}
	else if (StrEquals(option, "Shrunk"))
	{
		SSET_ICON_RESIZE_TYPE(*ps, ICON_RESIZE_TYPE_SHRUNK);
		option = PeekToken(rest, &rest);
	}
	else
	{
		SSET_ICON_RESIZE_TYPE(*ps, ICON_RESIZE_TYPE_NONE);
	}

	switch (GetIntegerArguments(rest, &rest, vals, 4))
	{
	case 0:

		vals[0] = vals[1] = UNSPECIFIED_ICON_DIMENSION;

	case 2:

		vals[2] = vals[0];
		vals[3] = vals[1];

	case 4:

		for (i = 0; i < 4; i++)
		{
			int use_default = 0;

			if (vals[i] != UNSPECIFIED_ICON_DIMENSION &&
			    (vals[i] < MIN_ALLOWABLE_ICON_DIMENSION ||
			     vals[i] > MAX_ALLOWABLE_ICON_DIMENSION))
			{
				fvwm_msg(
					ERR, "CMD_Style",
					"IconSize dimension (%d) not in valid"
					" range (%d-%d)",
					vals[i], MIN_ALLOWABLE_ICON_DIMENSION,
					MAX_ALLOWABLE_ICON_DIMENSION);
				use_default = 1;
			}


			else if (vals[i] == UNSPECIFIED_ICON_DIMENSION)
			{
				use_default = 1;
			}

			if (use_default)
			{


				vals[i] = i < 2 ? MIN_ALLOWABLE_ICON_DIMENSION :
					MAX_ALLOWABLE_ICON_DIMENSION;
			}
		}
		SSET_MIN_ICON_WIDTH(*ps, vals[0]);
		SSET_MIN_ICON_HEIGHT(*ps, vals[1]);
		SSET_MAX_ICON_WIDTH(*ps, vals[2]);
		SSET_MAX_ICON_HEIGHT(*ps, vals[3]);

		ps->flags.has_icon_size_limits = 1;
		ps->flag_mask.has_icon_size_limits = 1;
		ps->change_mask.has_icon_size_limits = 1;
		break;
	default:
		fvwm_msg(
			ERR, "CMD_Style",
			"IconSize requires exactly 0, 2 or 4"
			" numerical arguments");
		break;
	}

	return rest;
}

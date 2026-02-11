parse_and_set_window_style(char *action, char *prefix, window_style *ps)
{
	char *option;
	char *token;
	char *rest;
	Bool found;

	icon_boxes *cur_ib = NULL;

	while (isspace((unsigned char)*action))
	{
		action++;
	}

	while (action && *action && *action != '\n')
	{
		action = GetNextFullOption(action, &option);
		if (!option)
		{
			break;
		}
		token = PeekToken(option, &rest);
		if (!token)
		{
			free(option);
			break;
		}


		found = style_parse_one_style_option(
			token, rest, &rest, prefix, ps, &cur_ib);

		if (found == False)
		{
			fvwm_msg(
				ERR, "style_parse_and_set_window_style",
				"Bad style option: %s", option);


		}
		else if (rest != NULL)
		{
			rest = SkipSpaces(rest,NULL,0);
			if (*rest)
			{
				fvwm_msg(WARN,
					 "style_parse_and_set_window_style",
					 "Unconsumed argument in %s: %s",
					 option, rest);
			}
		}
		free(option);
	}

	return;
}

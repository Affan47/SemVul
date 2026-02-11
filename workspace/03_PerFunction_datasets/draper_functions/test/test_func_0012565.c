hexchat_get_prefs (hexchat_plugin *ph, const char *name, const char **string, int *integer)
{
	int i = 0;


	switch (str_hash (name))
	{
		case 0xf82136c4:
			*integer = fe_get_inputbox_cursor (ph->context);
			return 2;

		case 0xd1b:
			*integer = ph->context->server->id;
			return 2;
	}

	do
	{
		if (!g_ascii_strcasecmp (name, vars[i].name))
		{
			switch (vars[i].type)
			{
			case TYPE_STR:
				*string = ((char *) &prefs + vars[i].offset);
				return 1;

			case TYPE_INT:
				*integer = *((int *) &prefs + vars[i].offset);
				return 2;

			default:

				if (*((int *) &prefs + vars[i].offset))
					*integer = 1;
				else
					*integer = 0;
				return 3;
			}
		}
		i++;
	}
	while (vars[i].name);

	return 0;
}

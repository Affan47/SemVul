cfg_get_bool (char *var)
{
	int i = 0;

	do
	{
		if (!g_ascii_strcasecmp (var, vars[i].name))
		{
			return *((int *) &prefs + vars[i].offset);
		}
		i++;
	}
	while (vars[i].name);

	return -1;
}

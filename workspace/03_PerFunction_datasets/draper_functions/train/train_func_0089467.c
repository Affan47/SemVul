get_variable(const char *var)
{
	int i;

	for (i = 0; i < CFG_VARIABLES; i++)
		if (strcmp(config[i].var,var) == 0)
			return config + i;
	return 0;
}

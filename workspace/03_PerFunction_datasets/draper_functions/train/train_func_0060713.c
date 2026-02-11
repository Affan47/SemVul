vartab_lookup_name(const char *var)
{
	int	i;

	for (i = 0; apc_vartab[i].name != NULL; i++)
		if (!(apc_vartab[i].flags & APC_DEPR) &&
		    !strcasecmp(apc_vartab[i].name, var))
			return &apc_vartab[i];

	return NULL;
}

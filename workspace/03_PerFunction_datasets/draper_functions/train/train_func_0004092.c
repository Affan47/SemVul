psmouse_check_pnp_id(const char *id, const char * const ids[])
{
	int i;

	for (i = 0; ids[i]; i++)
		if (!strcasecmp(id, ids[i]))
			return true;

	return false;
}

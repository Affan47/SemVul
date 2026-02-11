ca_filter(void *unused, void *key, char **name, section_t **section)
{
	if (streq((*section)->name, "%default"))
	{
		return FALSE;
	}
	*name = (*section)->name;
	return TRUE;
}

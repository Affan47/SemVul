ecpg_find_desc(int line, const char *name)
{
	struct descriptor *desc;

	for (desc = get_descriptors(); desc; desc = desc->next)
	{
		if (strcmp(name, desc->name) == 0)
			return desc;
	}

	ecpg_raise(line, ECPG_UNKNOWN_DESCRIPTOR, ECPG_SQLSTATE_INVALID_SQL_DESCRIPTOR_NAME, name);
	return NULL;
}

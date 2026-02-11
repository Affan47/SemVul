_NameToInfo(name)
	CONST char *name;
{
	DBTCL_INFO *p;

	if (name == NULL)
		return (NULL);
	LIST_FOREACH(p, &__db_infohead, entries)
		if (strcmp(name, p->i_name) == 0)
			return (p);
	return (NULL);
}

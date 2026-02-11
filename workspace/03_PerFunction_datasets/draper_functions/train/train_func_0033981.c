column_name_to_id(const char *name, size_t namesz)
{
	int i;

	for (i = 0; i < __NCOLUMNS; i++) {
		const char *cn = infos[i].name;

		if (!strncasecmp(name, cn, namesz) && !*(cn + namesz))
			return i;
	}
	warnx(_("unknown column: %s"), name);
	return -1;
}

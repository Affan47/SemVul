rlookup_binding(FILE *f, char **map_wwid, char *map_alias)
{
	char buf[LINE_MAX];
	unsigned int line_nr = 0;
	int id = 0;

	*map_wwid = NULL;

	while (fgets(buf, LINE_MAX, f)) {
		char *c, *alias, *wwid;
		int curr_id;

		line_nr++;
		c = strpbrk(buf, "#\n\r");
		if (c)
			*c = '\0';
		alias = strtok(buf, " \t");
		if (!alias)
			continue;
		curr_id = scan_devname(alias);
		if (curr_id >= id)
			id = curr_id + 1;
		wwid = strtok(NULL, " \t");
		if (!wwid){
			condlog(3,
				"Ignoring malformed line %u in bindings file",
				line_nr);
			continue;
		}
		if (strcmp(alias, map_alias) == 0){
			condlog(3, "Found matching alias [%s] in bindings file."
				"\nSetting wwid to %s", alias, wwid);
			*map_wwid = strdup(wwid);
			if (*map_wwid == NULL)
				condlog(0, "Cannot copy alias from bindings "
					"file : %s", strerror(errno));
			return id;
		}
	}
	condlog(3, "No matching alias [%s] in bindings file.", map_alias);
	return id;
}

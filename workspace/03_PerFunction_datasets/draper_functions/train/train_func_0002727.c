dbg_maps_lookup(
					proc_t *p,
					int flags,
					const char *name,
					mapping_t ***mappings)
{
	int c;
	mapping_t **maps, *map, **bak;

	*mappings = NULL;


	for (map=p->maps, c=0, maps=NULL; map; map=map->next) {


		if (flags && (map->flags != flags))
			continue;
		if (name && !strstr(map->name, name))
			continue;
		if (0) {
		fprintf(stderr, "==> %s %s %s\n", map->name, name,
				strstr(map->name, name) ?
				strstr(map->name, name) : "NULL");
	}

		bak = maps;
		maps = realloc(maps, (c+1)*sizeof(mapping_t *));
		if (!maps) {
			if (bak)
				free(bak);
			return DBGERR_ENOMEM;;
		}
		maps[c] = map;
		++c;
	}

	*mappings = maps;

	return c;
}

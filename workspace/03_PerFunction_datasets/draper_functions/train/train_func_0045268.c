dbg_map_lookup(proc_t *p, int flags, const char *name)
{
	int ret;
	mapping_t **maps, *map;

	ret = dbg_maps_lookup(p, flags, name, &maps);
	fprintf(stderr, "retcount: %i\n", ret);
	map = (ret == 1 ? *maps : NULL);

	if (ret > 0)
		free(maps);

	return map;
}

lookup_close_lookup_instances(struct map_source *map)
{
	struct map_source *instance;

	instance = map->instance;
	while (instance) {
		lookup_close_lookup_instances(instance);
		instance = instance->next;
	}

	if (map->lookup) {
		close_lookup(map->lookup);
		map->lookup = NULL;
	}
}

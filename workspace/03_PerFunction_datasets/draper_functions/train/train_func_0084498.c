pc_map_has_value_for(struct pc_map *map, unsigned long pc)
{
	if (pc >= (unsigned long) map->size)
		return false;

	return map->map[pc].nr_values > 0;
}

default_erasesize(struct map_info *map)
{
	const __be32 *erase_size = NULL;

	erase_size = of_get_property(map->device_node, "erase-size", NULL);

	return !erase_size ? map->size : be32_to_cpu(*erase_size);
}

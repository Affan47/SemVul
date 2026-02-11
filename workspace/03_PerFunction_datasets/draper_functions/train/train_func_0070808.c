apprentice_unmap(struct magic_map *map)
{
	if (map == NULL)
		return;
	if (map->p == NULL)
		return;
#ifdef QUICK
	if (map->len)
		(void)munmap(map->p, map->len);
	else
#endif
		free(map->p);
	free(map);
}

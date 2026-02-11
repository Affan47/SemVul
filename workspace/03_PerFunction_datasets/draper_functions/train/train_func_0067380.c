map_free(struct map **map)
{
	struct map *tmp = *map;

	while (tmp) {
		free(tmp->key);
		free(tmp->data);
		tmp = tmp->next;
		free(*map);
		*map = tmp;
	}
}

ast_realtime_is_mapping_defined(const char *family)
{
	struct ast_config_map *map;
	ast_mutex_lock(&config_lock);

	for (map = config_maps; map; map = map->next) {
		if (!strcasecmp(family, map->name)) {
			ast_mutex_unlock(&config_lock);
			return 1;
		}
	}

	ast_mutex_unlock(&config_lock);

	return 0;
}

kui_ms_register_map(struct kui_map_set *kui_ms,
        const char *key_data, const char *value_data)
{
    struct kui_map *map;

    if (!kui_ms)
        return -1;

    map = kui_map_create(key_data, value_data);

    if (!map)
        return -1;

    if (std_list_insert_sorted(kui_ms->maps, map,
                    kui_map_compare_callback) == -1)
        return -1;

    if (kui_tree_insert(kui_ms->ktree, map->literal_key, map) == -1)
        return -1;

    return 0;
}

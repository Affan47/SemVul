insert(ALI_MAP * in_map, float costs)
{
    unsigned long   i;

    calls++;
    if (map == 0) {
        map = in_map;
        cost_of_binding = costs;
    } else {
        if (costs > cost_of_binding) {
            delete          in_map;
            return;
        }
        if (map->first_base() != in_map->first_base() ||
            map->last_base() != in_map->last_base() ||
            map->first_reference_base() != in_map->first_reference_base() ||
            map->last_reference_base() != in_map->last_reference_base()) {
            ali_fatal_error("Incompatible maps",
                            "ali_prealigner_mask::insert()");
        }
        if (costs < cost_of_binding) {
            delete          map;
            map = in_map;
            cost_of_binding = costs;
            last_new = calls;
            last_joins = 0;
            return;
        }
        joins++;
        last_joins++;
        for (i = map->first_base(); i <= map->last_base(); i++)
            if ((!map->is_undefined(i)) && map->position(i) != in_map->position(i))
                map->undefine(i);
        delete          in_map;
    }
}

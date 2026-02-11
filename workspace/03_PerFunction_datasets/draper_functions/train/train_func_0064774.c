put_floor(mapstruct *map, char **layout, int x, int y, object *floor_arch) {
    int dx, dy;
    object *floor;

    floor = arch_to_object(floor_arch->arch);
    object_insert_in_map_at(floor, map, floor, INS_NO_MERGE|INS_NO_WALK_ON, x, y);

    for (dx = -1; dx < 2; dx++) {
        for (dy = -1; dy < 2; dy++) {
            if (GET_MAP_OB(map, x+dx, y+dy) == NULL && can_propagate(layout[x+dx][y+dy]))
                put_floor(map, layout, x+dx, y+dy, floor_arch);
        }
    }
}

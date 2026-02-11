map_find_by_type(mapstruct *m, int x, int y, uint8 type) {
    if (out_of_map(m, x, y)) {
        LOG(llevError, "Present called outside map.\n");
        return NULL;
    }

    FOR_MAP_PREPARE(m, x, y, tmp)
        if (tmp->type == type)
            return tmp;
    FOR_MAP_FINISH();

    return NULL;
}

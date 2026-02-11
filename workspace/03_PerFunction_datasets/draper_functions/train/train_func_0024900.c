calculate_difficulty(mapstruct *m) {
    archetype *at;
    int x, y;
    int diff = 0;
    int i;
    sint64 exp_pr_sq, total_exp = 0;

    if (MAP_DIFFICULTY(m)) {
        return MAP_DIFFICULTY(m);
    }

    for (x = 0; x < MAP_WIDTH(m); x++)
        for (y = 0; y < MAP_HEIGHT(m); y++)
            FOR_MAP_PREPARE(m, x, y, op) {
                if (QUERY_FLAG(op, FLAG_MONSTER))
                    total_exp += op->stats.exp;
                if (QUERY_FLAG(op, FLAG_GENERATOR)) {
                    total_exp += op->stats.exp;
                    at = get_archetype_by_type_subtype(GENERATE_TYPE(op), -1);
                    if (at != NULL)
                        total_exp += at->clone.stats.exp*8;
                }
            } FOR_MAP_FINISH();

    exp_pr_sq = ((double)1000*total_exp)/(MAP_WIDTH(m)*MAP_HEIGHT(m)+1);
    diff = 20;
    for (i = 1; i < 20; i++)
        if (exp_pr_sq <= level_exp(i, 1.0)) {
            diff = i;
            break;
        }

    return diff;
}

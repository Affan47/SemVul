singing(object *pl, int dir, object *skill) {
    int i, exp = 0, chance, mflags;
    object *tmp;
    mapstruct *m;
    sint16  x, y;
    char name[MAX_BUF];
    const char *value;

    if (pl->type != PLAYER)
        return 0;

    draw_ext_info_format(NDI_UNIQUE, 0, pl, MSG_TYPE_SKILL, MSG_TYPE_SKILL_SUCCESS,
                         "You sing");
    for (i = dir; i < (dir+MIN(skill->level, SIZEOFFREE)); i++) {
        x = pl->x+freearr_x[i];
        y = pl->y+freearr_y[i];
        m = pl->map;

        mflags = get_map_flags(m, &m, x, y, &x, &y);
        if (mflags&P_OUT_OF_MAP)
            continue;
        if (!(mflags&P_IS_ALIVE))
            continue;

        tmp = NULL;
        FOR_MAP_PREPARE(m, x, y, tmp2) {
            tmp2 = HEAD(tmp2);
            if (QUERY_FLAG(tmp2, FLAG_MONSTER)) {
                tmp = tmp2;
                break;
            }

            if (tmp2->type == PLAYER) {
                tmp = tmp2;
                break;
            }
        } FOR_MAP_FINISH();


        if (tmp
        && QUERY_FLAG(tmp, FLAG_MONSTER)
        && !QUERY_FLAG(tmp, FLAG_NO_STEAL)
        && !QUERY_FLAG(tmp, FLAG_SPLITTING)
        && !QUERY_FLAG(tmp, FLAG_HITBACK)
        && (tmp->level <= skill->level)
        && !QUERY_FLAG(tmp, FLAG_UNDEAD)
        && !QUERY_FLAG(tmp, FLAG_UNAGGRESSIVE)
        && !QUERY_FLAG(tmp, FLAG_FRIENDLY)) {


            chance = skill->level*2+(pl->stats.Cha-5-tmp->stats.Int)/2;

            value = object_get_value(tmp, "no_mood_change");
            if (value && strcmp(value, "1") == 0)
                chance = 0;

            if (chance && tmp->level*2 < random_roll(0, chance-1, pl, PREFER_HIGH)) {
                SET_FLAG(tmp, FLAG_UNAGGRESSIVE);
                query_name(tmp, name, MAX_BUF);
                draw_ext_info_format(NDI_UNIQUE, 0, pl, MSG_TYPE_SKILL, MSG_TYPE_SKILL_SUCCESS,
                                     "You calm down the %s",
                                     name);


                if (!QUERY_FLAG(tmp, FLAG_NO_STEAL))
                    exp += calc_skill_exp(pl, tmp, skill);
                SET_FLAG(tmp, FLAG_NO_STEAL);
            } else {
                query_name(tmp, name, MAX_BUF);
                draw_ext_info_format(NDI_UNIQUE, 0, pl, MSG_TYPE_SKILL, MSG_TYPE_SKILL_FAILURE,
                                     "Too bad the %s isn't listening!",
                                     name);
                SET_FLAG(tmp, FLAG_NO_STEAL);
            }
        }
    }
    return exp;
}
